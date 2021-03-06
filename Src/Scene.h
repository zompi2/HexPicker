#pragma once

/**
 * Simple Hex Picker
 *
 * This is a scene class. It contains all elements displaying on the scene
 * in this example it will be board with tiles.
 *
 * (c) 2015 Damian Nowakowski
 */

#include <SFML/Graphics.hpp>

class Board;

class Scene
{
public:
	/**
	 * Simple constructor and destructor
	 */
	Scene();
	~Scene();

	/**
	 * Draw whole scene.
	 * @param window - pointer to the SFML Window
	 */
	void Draw(sf::RenderWindow* window);

	/**
	 * Update the scene in this tick.
	 * @param deltaTime - the time of passed tick.
	 */
	void Update(float deltaTime);

private:

	Board* board;	///< Pointer to the board
};