/**
 * Simple Hex Picker
 *
 * This is a scene class. It contains all elements displaying on the scene
 * in this example it will be board with tiles.
 *
 * (c) 2015 Damian Nowakowski
 */

#include "Scene.h"
#include "BoardPointy.h"
#include "BoardFlat.h"
#include "Engine.h"

/**
 * Simple constructor
 */
Scene::Scene()
{
	// Get the ini reader for future use
	INIReader* localConfig = ENGINE->config;

	// Create the flat oriented or pointy oriented board, depending upon the ini file.
	if (localConfig->GetBoolean("Tiles", "Flat", false) == true)
	{
		board = new BoardFlat(	localConfig->GetInteger("Window", "Width", 800), 
								localConfig->GetInteger("Window", "Width", 600),
								localConfig->GetInteger("Tiles", "Rows", 1),
								localConfig->GetInteger("Tiles", "Columns", 1));
	}
	else
	{
		board = new BoardPointy(	localConfig->GetInteger("Window", "Width", 800), 
									localConfig->GetInteger("Window", "Width", 600),
									localConfig->GetInteger("Tiles", "Rows", 1),
									localConfig->GetInteger("Tiles", "Columns", 1));
	}
}

/**
 * Draw whole scene.
 * @param window - pointer to the SFML Window
 */
void Scene::Draw(sf::RenderWindow* window)
{
	board->Draw(window);
}

/**
 * Update the scene in this tick.
 * @param deltaTime - the time of passed tick.
 */
void Scene::Update(float deltaTime)
{
	board->Update(deltaTime);
}

/**
 * Simple destructor cleaning the scene
 */
Scene::~Scene()
{
	delete board;
}