#pragma once

#include <vector>
#include "ShipTypeEnum.h"
#include "TileStateEnum.h"

// Utility functions to return ship data
namespace ShipUtilities
{
	int getShipSize(const int shipType);

	// Use the int ship type to get the ShipTypeEnum.
	ShipTypeEnum getShipTypeFromBoard(const int shiptype);

	// Use the int tile state to get the TileStateEnum.
	TileStateEnum getTileStateFromBoard(const int tileState);

	// Set the tile state of the tile by replacing the 10's digit with the TileStateEnum value.
	void setTileState(std::vector<int>* board, const int tileIndex, const TileStateEnum tileState);

	// Whether the shipType represents a vaild ship.
	bool isShipType(const int shipType);
}