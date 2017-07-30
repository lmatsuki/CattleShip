#include "AI.h"
#include "Utilities.h"
#include "ShipUtilities.h"

AI::AI()
{

}

void AI::randomPlaceShips(Player * player)
{	
	int placedShipIndex = -1;
	bool shipHorizontal = false;
	int currentShip = player->currentShipSelection;
	const int dimension = player->board.getDimensions();
	int randX, randY, boardIndex;
	// Randomize the seed
	srand(time(NULL));

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
	Easy:
		return randomlyFire(player);
	Medium:
		break;
	Hard:
		break;
	default:
		return Invalid;
	}
}

TileStateEnum AI::randomlyFire(Player * player)
{
	const int totalTiles = player->board.getTotalTiles();
	TileStateEnum tileState = Invalid;
	int tileIndex = 0;

	// Randomize the seed
	srand(time(NULL));

	while (tileState == Invalid)
	{
		tileIndex = rand() % totalTiles;
		tileState = player->board.checkFiredTileIndex(tileIndex);
	}

	return tileState;
}


