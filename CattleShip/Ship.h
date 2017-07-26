#pragma once

#include <vector>
#include "ShipTypeEnum.h"
#include "ShipOrientation.h"

class Ship
{
public:
	Ship(const ShipTypeEnum shipType, const int shipSize);
	virtual ~Ship() {};
	virtual const ShipTypeEnum getShipType();
	virtual const int getShipSize();

	const ShipTypeEnum shipType;
	const int shipSize;
	ShipOrientation orientation;
};