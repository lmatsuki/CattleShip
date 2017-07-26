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
}
