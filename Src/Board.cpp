/**
 * Hex Picker example.
 *
 * The base of the board where tiles will be put.
 * Other kind of boards will inherit from this one.
 *
 * This file is a part of a project from http://zompi.pl/simple-hex-picker/
 * (c) 2015 Damian Nowakowski
 */

#include "Board.h"
#include "Tile.h"

/**
 * Base constructor that sets base board parameters.
 * Other types of boards might need more operations during
 * construction.
 * @param width		- desirable width of the board (it will be square anyway)
 * @param height	- desirable height of the board (it will be square anyway)
 * @param rows		- how many rows of tiles there will be
 * @param columns	- how many columns of tiles there will be
 */
Board::Board(int width, int heigth, int rows, int columns)
{
	/// Remember important values from constructor
	this->width		= width;
	this->heigth	= heigth;
	this->rows		= rows;
	this->columns	= columns;
	
	// Set the size of the square board (the smaller edge)
	boardSize = width;
	if (heigth < boardSize)
	{
		boardSize = heigth;
	}

	// Set the pointer tho the hovered tile to null for safety
	currentlyHoveredTile = nullptr;
}

/**
 * Update the whole board
 * @param deltaTime - time of current tick
 */
void Board::Update(float deltaTime)
{
	//Remember which tile was hovered in previous tick
	Tile * oldTile = currentlyHoveredTile;

	HandleInput();

	//If mouse is over another tile
	if (oldTile != currentlyHoveredTile)
	{
		//Do actions for hover in and hover out
		if (currentlyHoveredTile != NULL)
		{
			currentlyHoveredTile->OnMouseHoverIn();
		}
		if (oldTile != NULL)
		{
			oldTile->OnMouseHoverOut();
		}
	}
}

/**
 * Draw the whole board
 * @param window - pointer to the SFML RenderWindow
 */
void Board::Draw(sf::RenderWindow* window)
{
	//Draw all tiles
	for (auto &column : tiles)
	{
		for (auto &tile : column)
		{
			tile->Draw(window);
		}
	}
}

/**
 * Destructor that will run in any kind of board.
 * It will clear all the tiles.
 */
Board::~Board()
{
	currentlyHoveredTile = nullptr;

	for (auto &column : tiles)
	{
		for (auto &tile : column)
		{
			delete tile;
		}
		column.clear();
	}
	tiles.clear();
}