/**
 * Hex Picker example.
 *
 * This is an engine class where the core application's mechanics
 * are stored and processed.
 *
 * This file is a part of a project from http://zompi.pl/simple-hex-picker/
 * (c) 2015 Damian Nowakowski
 */

#include "Engine.h"
#include "Scene.h"

// Set the default value of instance pointer to avoid memory ridings
Engine * Engine::engine = NULL;

/**
 * Get the engine instance (singleton).
 */
Engine * Engine::GetEngine()
{
	return engine;
}

/**
 * Create the engine. Must be used first.
 */
void Engine::Create()
{
	if (engine == NULL)
	{
		engine = new Engine();
	}
}

/**
 * Initialize the engine. Must be used after creation.
 * It can't be inside creation, because some objects needs the
 * already existing engine instance.
 */
void Engine::Init()
{
	config = new INIReader(CONFIG_PATH);

	// Create and initialize window.
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	window.create(sf::VideoMode(
		config->GetInteger("Window", "Width", 0), 
		config->GetInteger("Window", "Width", 0)), 
		config->Get("Window", "Title", ""),
		sf::Style::Titlebar | sf::Style::Close, 
		settings
	);

	// Create a scene
	scene = new Scene();

	// Set the initial values for timers
	updateTimer = 0;
	renderTimer = 0;

	// Say that engine is currently running
	isRunning = true;

	// Restart the clock for proper tick counting
	clock.restart();
}

/**
 * Clean the engine. Use it before tha application close.
 */
void Engine::Clean()
{
	if (engine != NULL)
	{
		delete engine;
		engine = NULL;
	}
}

/**
 * Check if the engine is running. Best use to decide if
 * application has to exit.
 * @returns true if engine is running.
 */
bool Engine::IsRunning()
{
	return engine && isRunning;
}

/**
 * Stop the engine. Use it when client want to close the applictaion.
 */
void Engine::StopEngine()
{
	isRunning = false;
}

/**
 * Poll all engine events. Best use inside the main loop.
 */
void Engine::Poll()
{
	// Safety check if the engine is running for sure
	if (isRunning == false)
	{
		return;
	}

	// Calculate the one tick time
	float deltaTime = clock.restart().asSeconds();

	// Increment timers with the one tick time
	updateTimer += deltaTime;
	renderTimer += deltaTime;

	/// The following conditions are for updating and rendering the application
	/// only when it is necessary. No more than their periods.
	// When it is time for an update:
	if (updateTimer >= UPDATE_PERIOD)
	{
		// Update it as many times as the update periods passed 
		// from the previous tick.
		float updateDeltaTime = 0;
		while (updateTimer >= UPDATE_PERIOD)
		{
			updateDeltaTime += UPDATE_PERIOD;
			updateTimer -= UPDATE_PERIOD;
		}
		Update(updateDeltaTime);
	}

	// Safety check if the engine is running for sure
	// The state could change after the update
	if (isRunning == false)
	{
		return;
	}
	
	// When it is time for render
	if (renderTimer >= RENDER_PERIOD)
	{
		// Just render it once and set remaining render time.
		while (renderTimer > RENDER_PERIOD)
		{
			renderTimer -= RENDER_PERIOD;
		}
		Draw();
	}
}

/**
 * Method for updating all game
 * @param updateDeltaTime - the time of passed tick.
 */
void Engine::Update(float updateDeltaTime)
{
	// Check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			StopEngine();
			return;
		}
	}

	// Update the scene
	scene->Update(updateDeltaTime);
}

/**
 * Method for drawing all game
 */
void Engine::Draw()
{
	// Clear the window with black color
	window.clear(sf::Color::Black);

	// Draw the scene
	scene->Draw(&window);

	// End the current frame
	window.display();
}

/**
 * Simple destructor
 */
Engine::~Engine()
{
	delete scene;
}