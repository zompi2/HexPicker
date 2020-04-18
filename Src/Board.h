#pragma once

/**
 * Simple Hex Picker.
 *
 * The base of the board where tiles will be put.
 * Other kind of boards will inherit from this one.
 *
 * (c) 2015 Damian Nowakowski
 */

#include <SFML/Graphics.hpp>

// The approximate value of sin(60)
#define SIN60 0.8660254038f	

// The value of sin(30)
#define SIN30 0.5f

// Predefine needed class
class Tile;

class Board
{
public:
	/**
	 * Base constructor that sets base board parameters.
	 * Other types of boards might need more operations during
	 * construction.
	 * @param width		- desirable width of the board (it will be square anyway)
	 * @param height	- desirable height of the board (it will be square anyway)
	 * @param rows		- how many rows of tiles there will be
	 * @param columns	- how many columns of tiles there will be
	 */
	Board(int width, int heigth, int rows, int columns);
	
	/**
	 * Destructor that will run in any kind of board.
	 * It will clear all the tiles.
	 */
	virtual ~Board();

	/**
	 * Handle the input on the board.
	 * This method checks over which tile the mouse hovers.
	 * Because of different types of boards this method MUST be
	 * override.
	 */
	virtual void HandleInput() = 0;

	/**
	 * Draw the whole board
	 * @param window - pointer to the SFML RenderWindow
	 */
	void Draw(sf::RenderWindow* window);

	/**
	 * Update the whole board
	 * @param deltaTime - time of current tick
	 */
	void Update(float deltaTime);

protected:
	int width, heigth;						///< With and heith of the board (the same as the window)
	int rows, columns;						///< Number of rows and columns on board
	int boardSize;							///< Length of the board edge (board is always a rectangle!)
	float tileR;							///< Radius of the one tile (length of it's edge)

	std::vector<std::vector<Tile*>> tiles;	///< 2D vector (array) of tiles on board
	Tile * currentlyHoveredTile;			///< Pointer to the tile above which the mouse is
};