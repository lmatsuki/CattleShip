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
