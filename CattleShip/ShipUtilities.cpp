#include "ShipUtilities.h"

// Utility functions to return ship data
namespace ShipUtilities
{
	int getShipSize(const int shipType)
	{
		switch ((ShipTypeEnum)shipType)
		{
		case Cruiser:		return 3;
		case Carrier:		return 5;
		case Battleship:	return 4;
		case Submarine:		return 3;
		case Destroyer:		return 2;
		case Missle:		return 1;
		default:			return 0;
		}
	}

	// Use the int ship type to get the ShipTypeEnum (1's digit).
	ShipTypeEnum getShipTypeFromBoard(const int shiptype)
	{
		return (ShipTypeEnum)(shiptype % 10);
	}

	// Use the int tile state to get the TileStateEnum (10's digit).
	TileStateEnum getTileStateFromBoard(const int tileState)
	{
		return (TileStateEnum)(tileState / 10);
	}

	// Set the tile state of the tile by replacing the 10's digit with the TileStateEnum value.
	void setTileState(std::vector<int>* board, const int tileIndex, const TileStateEnum tileState)
	{
		int currentTileValue = board->at(tileIndex);
		int shipType = getShipTypeFromBoard(currentTileValue);
		board->at(tileIndex) = ((int)tileState * 10) + shipType;
	}

	// Whether the shipType represents a vaild ship.
	bool isShipType(const int shipType)
	{
		return shipType > 0 && shipType < 6;
	}
}
