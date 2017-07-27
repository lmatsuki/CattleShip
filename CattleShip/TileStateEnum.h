#pragma once

enum TileStateEnum
{
	Empty,		// Clicked on a fresh tile
	Missed,		// Clicked a valid tile with no ship
	Hit,		// Clicked a valid tile with ship
	Invalid,    // Clicked outside the board
};