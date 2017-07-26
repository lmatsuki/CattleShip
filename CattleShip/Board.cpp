#include "Board.h"
#include "ShipTypeEnum.h"
#include "Tile.h"

#include "Utilities.h"
#include "ShipUtilities.h"

Board::Board(int dimension, TextureManager* textureManager) : dimensions(dimension), 
	textureManager(textureManager), widthPercentage(0.8), heightPercentage(0.8)
{
	board = std::vector<int>(dimensions * dimensions, 0);
}

Board::~Board()
{
}

void Board::init(const sf::RenderWindow& window)
{
	setBoardSize(window);
	setBoardPosition(window);
	boardRect.setFillColor(sf::Color::Green);
	initializeTiles();
}

void Board::initializeTiles()
{
	sf::FloatRect globalBounds = boardRect.getGlobalBounds();
	float boardTop = globalBounds.top;
	float boardLeft = globalBounds.left;
	float tileWidth = globalBounds.width / dimensions;
	float tileHeight = globalBounds.height / dimensions;

	sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));
	tile.setOutlineThickness(2);
	tile.setOutlineColor(sf::Color::Black);
	tile.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < dimensions; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			tile.setPosition(sf::Vector2f(boardLeft + i * tileWidth, boardTop + j * tileHeight));
			tiles.push_back(tile);
		}
	}
}

void Board::render(sf::RenderWindow& window)
{
	window.draw(boardRect);

	// Draw grid lines
	sf::FloatRect globalBounds = boardRect.getGlobalBounds();
	float boardTop = globalBounds.top;
	float boardLeft = globalBounds.left;

	// Draw the background
	sf::Sprite sprite = textureManager->GetSpriteBySpriteType(SpriteGrass);
	sprite.setPosition(sf::Vector2f(boardLeft, boardTop));
	window.draw(sprite);

	int tilesSize = dimensions * dimensions;
	for (int i = 0; i < tilesSize; i++)
	{
		window.draw(tiles[i]);
		renderShip(board[i], tiles[i].getPosition(), window);
		// Render player/enemy specific ships with hit/miss marks

	}
}

void Board::renderShip(const int shipType, const sf::Vector2f position, sf::RenderWindow & window)
{
	// Offset for ship images
	sf::Vector2f adjustedPosition = sf::Vector2f(position.x - 15, position.y - 35);
	sf::Sprite sprite;

	switch ((ShipTypeEnum)shipType)
	{
	case Carrier:
		sprite = textureManager->GetSpriteByShipType(Carrier);
		sprite.setPosition(sf::Vector2f(position.x + 15, position.y + 5));
		sprite.setScale(1.0f, 1.0f);
		window.draw(sprite);
		break;
	case Cruiser:
		sprite = textureManager->GetSpriteByShipType(Cruiser);
		sprite.setPosition(adjustedPosition);
		sprite.setScale(0.85f, 0.85f);
		window.draw(sprite);
		break;
	case Battleship:
		sprite = textureManager->GetSpriteByShipType(Battleship);
		sprite.setPosition(adjustedPosition);
		sprite.setScale(0.85f, 0.85f);
		window.draw(sprite);
		break;
	case Submarine:
		sprite = textureManager->GetSpriteByShipType(Submarine);
		sprite.setPosition(adjustedPosition);
		sprite.setScale(0.85f, 0.85f);
		window.draw(sprite);
		break;
	case Destroyer:
		sprite = textureManager->GetSpriteByShipType(Destroyer);
		sprite.setPosition(adjustedPosition);
		sprite.setScale(0.85f, 0.85f);
		window.draw(sprite);
		break;
	}
}

void Board::setBoardPosition(const sf::RenderWindow& window)
{
	float xPos = window.getSize().x * (1 - widthPercentage) / 2;
	float yPos = window.getSize().y * (1 - heightPercentage);
	float yBottomOffset = 10;
	boardRect.setPosition(xPos, yPos - yBottomOffset);
}

void Board::setBoardSize(const sf::RenderWindow& window)
{
	float width = window.getSize().x * widthPercentage;
	float height = window.getSize().y * heightPercentage;
	boardRect.setSize(sf::Vector2f(width, height));
}

void Board::setBoardFillColor(const sf::Color color)
{
	boardRect.setFillColor(color);
}

void Board::setBoardPiece(const int boardIndex, const int shipType, const bool shipHorizontal)
{
	int shipSize = ShipUtilities::getShipSize(shipType);
	for (int i = 0; i < shipSize; i++)
	{
		if (i == 0)
		{
			// Set the center of the ship
			board[boardIndex] = shipType;
		}
		else
		{
			int offSet = (i + 1) / 2;
			if (i % 2 == 1)
				offSet *= -1;
			if (shipHorizontal)
				offSet = offSet * dimensions;
			else if (offSet > 2)
				offSet--;

			board[boardIndex + offSet] = shipType;
		}
	}
}

void Board::clearOutlineColors()
{
	int tilesSize = dimensions * dimensions;
	for (int i = 0; i < tilesSize; i++)
	{
		tiles[i].setOutlineColor(sf::Color::Black);
	}
}

// Gets the tile index if clicked inside the board. Returns as soon as the tile is found.
int Board::getTileByCoords(const sf::Vector2f mousePosition)
{
	const int tilesSize = dimensions * dimensions;
	int tilePosition = -1;
	for (int i = 0; i < tilesSize; i++)
	{
		if (tiles[i].getGlobalBounds().contains(mousePosition))
		{
			return i;
		}
	}

	return tilePosition;
}

int Board::getValidTileByCoords(const sf::Vector2f mousePosition, const int shipType, const bool shipHorizontal)
{
	const int tilesSize = dimensions * dimensions;
	int tilePosition = -1;
	for (int i = 0; i < tilesSize; i++)
	{
		if (tiles[i].getGlobalBounds().contains(mousePosition))
		{
			tilePosition = i;
		}
	}

	// Short circuit, clicked outside tiles or on other ship
	if (tilePosition == -1 || board[tilePosition] != 0)
		return -1;

	// Check if the entire ship is inside the board
	int shipSize = ShipUtilities::getShipSize(shipType);
	if (getIsValidTileByIndex(tilePosition, shipSize, shipHorizontal))
		return tilePosition;
	else
		return -1;
}

bool Board::getIsValidTileByIndex(const int tilePosition, const int shipSize, const bool shipHorizontal)
{
	int tilePositionRow = tilePosition / 10;
	for (int i = 0; i < shipSize; i++)
	{
		if (i != 0)
		{
			int offSet = (i + 1) / 2;
			if (i % 2 == 1)
				offSet *= -1;
			if (shipHorizontal)
				offSet = offSet * dimensions;
			else if (offSet > 2)
				offSet--;

			// Early exit if invalid index (also checks they are in the same row if vertical)		
			// Added check for overlapping ships
			int checkPosition = tilePosition + offSet;
			if (checkPosition < 0 || checkPosition >= board.size() ||
				(!shipHorizontal && checkPosition / 10 != tilePositionRow) || board[checkPosition] != 0)
				return false;
		}
	}

	return true;
}

int Board::getDimensions()
{
	return dimensions;
}

//void Board::checkClickedTile(bool playerTurn, const sf::Vector2f position)
//{
//	// Parse the coordinates and check if it's a hit or miss
//	//bool hit = false;
//	//int row, col;
//	//row = col = 0;
//
//	// Change ShipTypeEnum depending on hit or miss
//	//UpdateHit(hit, playerTurn, col, row);
//	int tilesSize = dimensions * dimensions;
//	for (int i = 0; i < tilesSize; i++)
//	{
//		if (tiles[i].getGlobalBounds().contains(sf::Vector2f(position)))
//		{
//			int j = 5;
//		}
//	}
//}
//
//void Board::checkPlacedTile(const sf::Vector2f position)
//{
//	// Find the tile position the ship is placed in
//	int tilesSize = dimensions * dimensions;
//	int tilePosition = 0;
//	for (int i = 0; i < tilesSize; i++)
//	{
//		if (tiles[i].getGlobalBounds().contains(position))
//		{
//			tilePosition = i;
//		}
//	}
//
//	// Check if the tiles are valid
//	//for (int j = 0; j < 5; j++)
//	//	continue;
//
//}

void Board::checkMouseOver(const sf::Vector2f position, const int shipType, const bool shipHorizontal)
{
	// Then iterate through the tiles and check if moused over
	int tilesSize = dimensions * dimensions;
	bool selectedTile = false;
	int tileIndex = -1;
	for (int i = 0; i < tilesSize; i++)
	{
		if (!selectedTile && tiles[i].getGlobalBounds().contains(position))
		{
			selectedTile = true;
			tileIndex = i;
		}
		else
		{
			tiles[i].setOutlineColor(sf::Color::Black);
		}
	}

	if (tileIndex != -1)
	{
		int shipSize = ShipUtilities::getShipSize(shipType);
		sf::Color outlineColor;

		if (getValidTileByCoords(position, shipType, shipHorizontal) != -1)
			outlineColor = sf::Color::White;
		else
			outlineColor = sf::Color::Red;

		int tilePositionRow = tileIndex / 10;

		// Check if the entire ship can be placed
		for (int j = 0; j < shipSize; j++)
		{
			if (j == 0)
				tiles[tileIndex].setOutlineColor(outlineColor);
			else
			{
				int offSet = (j + 1) / 2;
				if (j % 2 == 1)
					offSet *= -1;
				if (shipHorizontal)
					offSet = offSet * dimensions;
				else if (offSet > 2)
					offSet--;

				// Highlight if same row and inside board
				int checkPosition = tileIndex + offSet;
				if (checkPosition >= 0 && checkPosition < board.size() &&
					(checkPosition / 10 == tilePositionRow || 
					(shipHorizontal && checkPosition / 10 != tilePositionRow)))
				{
					tiles[checkPosition].setOutlineColor(outlineColor);
				}
			}
		}
	}
}

TileStateEnum Board::checkFiredPosition(const sf::Vector2f mousePosition)
{
	int tileIndex = getTileByCoords(mousePosition);

	if (tileIndex == -1)
	{
		// Clicked outside the board
		return Invalid;
	}
	else
	{
		// Check whether a ship was hit or missed


		return Hit; // Set temporarily
	}		
}

bool Board::clickedInGrid(float xPos, float yPos)
{
	return boardRect.getGlobalBounds().contains(xPos, yPos);
}

void Board::updateHit(bool hit, bool playerTurn, int col, int row)
{	
	TileStateEnum shipType = hit ? Hit : Missed;
	//if (playerTurn)	
	//	std::get<0>(board[col][row]) = shipType;
	//else
	//	std::get<1>(board[col][row]) = shipType;
}
