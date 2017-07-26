#pragma once

enum TileStateEnum
{
	Invalid,		// Clicked outside the board
	Missed,		// Clicked a valid tile with no ship
	Hit,		// Clicked a valid tile with ship
};