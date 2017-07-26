#pragma once

#include "TileStateEnum.h"
#include "ShipTypeEnum.h"

class Tile
{
public:
	Tile();

private:
	int x;
	int y;
	TileStateEnum tileState;
	ShipTypeEnum shipType;
};