#include "AI.h"
#include "Utilities.h"
#include "ShipUtilities.h"

AI::AI() : lastHitShipType(None), sameShipHitCount(0), lastHitTileIndex(0), shipFoundIndex(0)
{
	// Randomize the seed (only once per application)
	srand(time(NULL));
}

AI::~AI()
{
	clearFallbackTileIndex();
}

void AI::randomPlaceShips(Player * player)
{	
	int placedShipIndex = -1;
	bool shipHorizontal = false;
	int currentShip = player->currentShipSelection;
	const int dimension = player->board.getDimensions();
	int randX, randY, boardIndex;

	while (currentShip <= LastShip)
	{
		// Pick random spot on grid		
		shipHorizontal = rand() % 2;
		randX = rand() % dimension;
		randY = rand() % dimension;
		boardIndex = Utilities::convertIndicesToIndex(randX, randY, dimension);

		// Check if that spot is valid
		placedShipIndex = player->board.getIsValidTileByIndex(boardIndex, ShipUtilities::getShipSize(currentShip), shipHorizontal) ? 0 : -1;
		if (placedShipIndex != -1)
		{
			placedShipIndex = -1;
			player->board.setBoardPiece(boardIndex, currentShip, shipHorizontal);
			currentShip++;
		}
	}
}

TileStateEnum AI::fireBasedOnDifficulty(Player * player, DifficultyEnum difficulty)
{
	switch (difficulty)
	{
	case Easy:		return randomlyFire(player);
	case Medium:	return smartFire(player, 50);
	case Hard:		return smartFire(player, 90);
	default:		return Invalid;
	}
}

TileStateEnum AI::randomlyFire(Player * player)
{
	const int totalTiles = player->board.getTotalTiles();
	TileStateEnum tileState = Invalid;
	int tileIndex = 0;

	while (tileState == Invalid)
	{
		tileIndex = rand() % totalTiles;
		tileState = player->board.checkFiredTileIndex(tileIndex);

		if (tileState == Hit)
			updateHitShipInfo(tileIndex, player);
	}

	return tileState;
}

TileStateEnum AI::smartFire(Player * player, const int smartChance)
{
	// Only calculate fire location if AI previously hit a ship
	if (lastHitShipType == None)
		return randomlyFire(player);

	TileStateEnum tileState = Invalid;
	int tileIndex = 0;

	// Should this move be a smart move?
	bool smartMove = getSmartOrStupid(smartChance);
	
	int currentAttempt = 0;

	// A ship was hit previously and is still alive
	while (tileState == Invalid)
	{
		DirectionEnum direction = getRandomDirection();
		tileIndex = getIndexOfDirection(direction, lastHitTileIndex);
				
		if (smartMove && player->board.getShipAliveByTile(tileIndex))
		{
			// A guaranteed Hit
			tileState = player->board.checkFiredTileIndex(tileIndex);
			updateHitShipInfo(tileIndex, player);
		}
		else if (!smartMove && player->board.getTileIsEmpty(tileIndex))
		{
			// A guaranteed Miss
			tileState = player->board.checkFiredTileIndex(tileIndex);
		}

		// Revert to fallbackTileIndex if there are no valid ships (to prevent infinite loop)
		if (smartMove && tileState == Invalid && noShipOnSurroundingTiles(player))
			lastHitTileIndex = getFallbackTileIndex();
		else if (!smartMove && tileState == Invalid && noEmptySurroundingTiles(player))
			smartMove = !smartMove;

		// To prevent getting stuck trying to find valid surrounding tiles (max of 10 attempts)
		if (currentAttempt >= 10)
			smartMove = false;
	}

	return tileState;
}

bool AI::noShipOnSurroundingTiles(Player* player)
{
	int tileIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		tileIndex = getIndexOfDirection((DirectionEnum)i, lastHitTileIndex);
		if (player->board.getShipAliveByTile(tileIndex))
			return false;
	}

	return true;
}

bool AI::noEmptySurroundingTiles(Player * player)
{
	int tileIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		tileIndex = getIndexOfDirection((DirectionEnum)i, lastHitTileIndex);
		if (player->board.getTileIsEmpty(tileIndex))
			return false;
	}

	return true;
}

void AI::updateHitShipInfo(const int tileIndex, Player* player)
{
	// This doesn't account for corner cases of hitting a different ship while
	// trying to destroy previous ship
	sameShipHitCount++;
	lastHitShipType = player->board.getShipByTile(tileIndex);
	shipFoundIndex = tileIndex;

	if (lastHitShipType != None && ShipUtilities::getShipSize(lastHitShipType) <= sameShipHitCount)
	{
		lastHitShipType = None;
		sameShipHitCount = 0;
		clearFallbackTileIndex();
	}
	else
	{
		// Set the initial fallback tile index
		if (sameShipHitCount == 1)
			fallbackTileIndex.push(tileIndex);
		else
			fallbackTileIndex.push(lastHitTileIndex);

		lastHitTileIndex = tileIndex;
	}
}

bool AI::getSmartOrStupid(const int smartChance)
{
	int chance = rand() % 100;
	return smartChance >= chance;
}

DirectionEnum AI::getRandomDirection()
{
	return (DirectionEnum)(rand() % 4);
}

int AI::getIndexOfDirection(const DirectionEnum direction, const int tileIndex)
{
	int finalIndex = tileIndex;
	switch (direction)
	{
	case Up:	finalIndex += -1;  break;
	case Down:	finalIndex += 1;   break;
	case Left:	finalIndex += -10; break;
	case Right:	finalIndex += 10;  break;
	default:	return tileIndex;
	}

	// Index bound checking
	if (finalIndex < 0 || finalIndex > 99)
		return tileIndex;
	else
		return finalIndex;
}

int AI::getFallbackTileIndex()
{
	if (fallbackTileIndex.empty())
		return 0;

	int tileIndex = fallbackTileIndex.top();
	fallbackTileIndex.pop();
	return tileIndex;
}

void AI::clearFallbackTileIndex()
{
	while (!fallbackTileIndex.empty())
		fallbackTileIndex.pop();
}

int AI::getShipFoundIndex()
{
	return shipFoundIndex;
}
