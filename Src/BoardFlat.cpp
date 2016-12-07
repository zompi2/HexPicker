/**
 * Hex Picker example.
 *
 * The board with the flat oriented tiles.
 *
 * This file is a part of a project from http://zompi.pl/simple-hex-picker/
 * (c) 2015 Damian Nowakowski
 */

#include "BoardFlat.h"
#include "Tile.h"
#include "Engine.h"

/**
 * The constructor specific for this kind of board.
 * It runs super constructor at the beginning.
 * @param width		- desirable width of the board (it will be squ
 * @param height	- desirable height of the board (it will be sq
 * @param rows		- how many rows of tiles there will be
 * @param columns	- how many columns of tiles there will be
 */
BoardFlat::BoardFlat(int width, int heigth, int rows, int columns)
	:Board(width, heigth, rows, columns)
{
	//Check how big can the tile be to fit them in width or height if board size
	int tileR_H = boardSize / (2.f + SIN60*(2.f * rows - 1.f));
	int tileR_W = boardSize / (1.5f * columns + 0.5f);

	//Pick the smaller option (this is the final size of one tile)
	tileR = tileR_W<tileR_H ? tileR_W : tileR_H;

	int startY = 0;
	int startX = 0;
	int yDir = 1;

	for (int c = 0; c < columns; c++)
	{
		std::vector<Tile*> newColumn;

		float centerX = tileR + startX;
		float centerY = tileR + startY;

		for (int r = 0; r < rows; r++)
		{
			newColumn.push_back(new Tile(c, r, centerX, centerY, tileR, true));
			centerY += 2*tileR*SIN60;
		}

		tiles.push_back(newColumn);

		startX += tileR*(2-SIN30);
		startY += tileR*SIN60*yDir;
		yDir *= -1;
	}
}

/**
 * An input handler that checks over which tile the mouse currently is.
 */
void BoardFlat::HandleInput()
{
	sf::Vector2i pos = sf::Mouse::getPosition(ENGINE->window);

	//Get relative to tiles field mouse position
	float mouseX = pos.x;
	float mouseY = pos.y - (tileR*(1 - SIN60));

	//If position is lesser than zero mouse was clicked outside the tiles field
	if (mouseX < 0 || mouseY < 0)
	{
		currentlyHoveredTile = nullptr;
		return;
	}

	//Those are lengths of specific sections of the tile
	//For more details see the tutorial
	float A = tileR;
	float B = A * SIN60;
	float C = A * SIN30;

	//Find out which major column and row we are on
	int column = (int)(mouseX / (A + C));
	int row = (int)(mouseY / B);

	//Compute the offset into these row and column
	float dx = mouseX - (float)column * (A + C);
	float dy = mouseY - (float)row * B;

	//Check if we are on the right side of the tile edge, or on the left side?
	if (((row ^ column) & 1) == 0)
	{
		dy = B - dy;
	}
	int right = (dx < ((C * dy) / B)) ? 1 : 0;
	
	//Fine-tune column and row
	row -= (row ^ column ^ right) & 1;
	row *= .5;
	column -= right;

	//If selected column or row is out of range mouse was clicked outside the tiles field
	if (row >= rows || column >= columns)
	{
		currentlyHoveredTile = nullptr;
		return;
	}

	//If selected column or row is less than 0 there is something wrong (probably clicked outside the tiles field)
	if (row < 0 || column < 0)
	{
		currentlyHoveredTile = nullptr;
		return;
	}

	//Remember which tile is under the mouse now
	currentlyHoveredTile = tiles[column][row];
}