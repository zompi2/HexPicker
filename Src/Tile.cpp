/**
 * Simple Hex Picker
 *
 * This is a class that represents one tile (hex) on the board.
 * It contains the information about the shape, position and state of tile.
 *
 * (c) 2015 Damian Nowakowski
 */

#include "Tile.h"

// The color of the normal tile
#define COLOR_NORMAL	sf::Color(175, 175, 175, 255)

// The color of the hovered tile
#define COLOR_HOVERED	sf::Color(255, 255, 255, 255)

/**
 * Constructor that sets up the tile.
 * @param column	- in which column this tile is
 * @param row		- in which row this tile is
 * @param centerX	- x position on the screen of the center of the tile
 * @param centerY	- y position on the screen of the center of the tile
 * @param radius	- radius of the tile (or the length of it's edge)
 * @param flat		- is this tile flat oriented?
 *					  (false for pointy oriented one)
 */
Tile::Tile(int column, int row, float centerX, float centerY, float radius, bool flat)
{
	/// Save the tile values
	this->column = column;
	this->row = row;
	this->centerX = centerX;
	this->centerY = centerY;
	this->radius = radius;

	// The sphere has 6 points so it will take form of hex
	// Also set size, position, outlines and color
	shape.setPointCount(6);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(0, 0, 0, 255));
	shape.setFillColor(COLOR_NORMAL);
	shape.setOrigin(radius, radius);
	shape.setRadius(radius);
	shape.setPosition(centerX, centerY);

	// If the tile is flat oriented the shape must be rotated
	if (flat == true)
	{
		shape.setRotation(90);
	}
}

/**
 * Draw the tile.
 * @param window - pointer to the SFML Window
 */
void Tile::Draw(sf::RenderWindow* window)
{
	window->draw(shape);
}

/**
 * What to do when mouse hover over the tile
 */
void Tile::OnMouseHoverIn()
{
	shape.setFillColor(COLOR_HOVERED);
}

/**
 * What to do when mouse hover out the tile
 */
void Tile::OnMouseHoverOut()
{
	shape.setFillColor(COLOR_NORMAL);
}
