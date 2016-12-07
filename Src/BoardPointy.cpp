/**
 * Hex Picker example.
 *
 * The board with the pointy oriented tiles.
 *
 * This file is a part of a project from http://zompi.pl/simple-hex-picker/
 * (c) 2015 Damian Nowakowski
 */

#include "BoardPointy.h"
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
BoardPointy::BoardPointy(int width, int heigth, int rows, int columns)
	:Board(width, heigth, rows, columns)
{
	//Check how big can the tile be to fit them in width or height if board size
	int tileR_W = boardSize / (2.f + SIN60*(2.f * columns - 1.f));
	int tileR_H = boardSize / (1.5f * rows + 0.5f);

	//Pick the smaller option (this is the final size of one tile)
	tileR = tileR_W<tileR_H ? tileR_W : tileR_H;

	int xDir = 1;	//direction of adding x values
	int startX = 0;	//x position of first column

	for (int c = 0; c < columns; c++)
	{
		//Set up new column of tiles
		std::vector<Tile*> newColumn;

		//Set up relative to {startX,0} center of the tile
		float centerX = tileR + startX;
		float centerY = tileR;

		for (int r = 0; r < rows; r++)
		{
			//Add new tile
			newColumn.push_back(new Tile(c, r, centerX, centerY, tileR, false));

			//Change center position and direction for adding x values for next tile
			centerY += tileR*(2-SIN30);
			centerX += tileR*SIN60*xDir;
			xDir *= -1;
		}

		//Add whole column and change x position for next column
		tiles.push_back(newColumn);
		startX += tileR * SIN60 * 2;
	}
}

/**
 * An input handler that checks over which tile the mouse currently is.
 */
void BoardPointy::HandleInput()
{
	sf::Vector2i pos = sf::Mouse::getPosition(ENGINE->window);

	//Get relative to tiles field mouse position
	float mouseX = pos.x - (tileR*(1 - SIN60));
	float mouseY = pos.y;

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
	int column = (int)(mouseX / B);
	int row = (int)(mouseY / (A + C));

	//Compute the offset into these row and column
	float dx = mouseX - (float)column * B;
	float dy = mouseY - (float)row * (A + C);

	//Check if we are on the top of the tile edge, or on the bottom?
	if (((row ^ column) & 1) == 0)
	{
		dx = B - dx;
	}
	int top = (dy < ((C * dx) / B)) ? 1 : 0;

	//Fine-tune column and row
	column -= (row ^ column ^ top) & 1;
	column *= .5;
	row -= top;

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