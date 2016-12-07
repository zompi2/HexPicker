#pragma once

/**
 * Hex Picker example.
 *
 * This is a class that represents one tile (hex) on the board.
 * It contains the information about the shape, position and state of tile.
 *
 * This file is a part of a project from http://zompi.pl/simple-hex-picker/
 * (c) 2015 Damian Nowakowski
 */

#include <SFML/Graphics.hpp>

class Tile
{
public:

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
	Tile(int column, int row, float centerX, float centerY, float radius, bool flat);

	/**
	 * Draw the tile.
	 * @param window - pointer to the SFML Window
	 */
	void Draw(sf::RenderWindow* window);

	/**
	 * What to do when mouse hover over the tile
	 */
	void OnMouseHoverIn();

	/**
	 * What to do when mouse hover out the tile
	 */
	void OnMouseHoverOut();
	
private:
	sf::CircleShape shape;		///< Shape of tile
	float radius;				///< Radius of tile (or length of hex edge, hexes are based on circle here)
	float centerX, centerY;		///< Relative to tiles field x,y position of center of the tile
	int column, row;			///< Index of column and row where tile is (starts with 0)
};