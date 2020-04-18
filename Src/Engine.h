#pragma once

/**
 * Simple Hex Picker
 *
 * This is an engine class where the core application's mechanics
 * are stored and processed.
 *
 * (c) 2015 Damian Nowakowski
 */

#include "inih/cpp/INIReader.h"

// Define Engine Helpers
#define ENGINE			Engine::GetEngine()
#define ENGINE_INIT		Engine::Create(); \
						ENGINE->Init();
#define ENGINE_CLEAN	Engine::Clean();

// Define the simple window getting
#define WINDOW			ENGINE->window
#define CONFIG			ENGINE->config


// Define the path to the configuration file
#define CONFIG_PATH		"Data/config.ini"

// Define the minimum update period (1/120 seconds)
#define UPDATE_PERIOD	(float)0.008333333

// Define the minimum render period (1/60 seconds)
#define RENDER_PERIOD	(float)0.016666667

#include <SFML/Graphics.hpp>

class Scene;

class Engine
{
public:

	INIReader*	config;			///< The configuration ini file reader
	sf::RenderWindow window;	///< Currently rendering window
	
	/**
	 * Get the engine instance (singleton).
	 */
	static Engine*	GetEngine();

	/**
	 * Create the engine. Must be used first.
	 */
	static void Create();

	/**
	 * Initialize the engine. Must be used after creation.
	 * It can't be inside creation, because some objects needs the 
	 * already existing engine instance.
	 */
	void Init();

	/**
	 * Clean the engine. Use it before tha application close.
	 */
	static void Clean();

	/**
	 * Check if the engine is running. Best use to decide if
	 * application has to exit.
	 * @returns true if engine is running.
	 */
	bool IsRunning();

	/**
	 * Stop the engine. Use it when client want to close the applictaion.
	 */
	void StopEngine();

	/**
	 * Poll all engine events. Best use inside the main loop.
	 */
	void Poll();

	/**
	 * Simple destructor
	 */
	~Engine();
	
private:

	/**
	 * Method for updating all game
	 * @param updateDeltaTime - the time of passed tick.
	 */
	void Update(float updateDeltaTime);
	
	/**
	 * Method for drawing all game
	 */
	void Draw();

	static Engine* engine;	///< The handler of the engine instance
	bool isRunning;			///< Flag telling if the engine is running
	
	sf::Clock clock;		///< The clock for counting update time

	float updateTimer;		///< Time of the one update tick
	float renderTimer;		///< Time of the one render tick	

	Scene* scene;
};

