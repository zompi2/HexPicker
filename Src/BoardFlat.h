#pragma once

/**
 * Hex Picker example.
 *
 * The board with the flat oriented tiles.
 *
 * This file is a part of a project from http://zompi.pl/simple-hex-picker/
 * (c) 2015 Damian Nowakowski
 */

#include "Board.h"

class BoardFlat : public Board
{
public:
	/**
	 * The constructor specific for this kind of board.
	 * It runs super constructor at the beginning.
	 * @param width		- desirable width of the board (it will be squ
	 * @param height	- desirable height of the board (it will be sq
	 * @param rows		- how many rows of tiles there will be
	 * @param columns	- how many columns of tiles there will be
	 */
	BoardFlat(int width, int heigth, int rows, int columns);

	/**
	 * An input handler that checks over which tile the mouse currently is.
	 */
	virtual void HandleInput() override;
};