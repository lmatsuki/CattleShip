#include "Ship.h"

Ship::Ship(const ShipTypeEnum shipType, const int shipSize) : shipType(shipType), shipSize(shipSize)
{
}

const ShipTypeEnum Ship::getShipType()
{
	return shipType;
}

const int Ship::getShipSize()
{
	return shipSize;;
}
