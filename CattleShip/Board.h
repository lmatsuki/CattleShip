#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TileStateEnum.h"

class Board
{
public:
	Board(int dimension, TextureManager* textureManager);
	~Board();
	void init(const sf::RenderWindow& window);
	void initializeTiles();
	void render(sf::RenderWindow& window, const bool renderShips);
	void renderShip(const int shipType, const sf::Vector2f position, sf::RenderWindow& window);
	void renderTile(const int tileState, const sf::Vector2f position, sf::RenderWindow& window);

	void setBoardPosition(const sf::RenderWindow& window);
	void setBoardSize(const sf::RenderWindow& window);
	void setBoardFillColor(const sf::Color color);
	void setBoardPiece(const int boardIndex, const int shipType, const bool shipHorizontal);
	TileStateEnum setFiredTileIndex(const int tileIndex);
	void clearOutlineColors();
	void clearBoard();

	int getTileByCoords(const sf::Vector2f mousePosition);
	int getValidTileByCoords(const sf::Vector2f mousePosition, const int shipType, const bool shipHorizontal);
	bool getIsValidTileByIndex(const int tilePosition, const int shipSize, const bool shipHorizontal);
	bool getShipAliveByTile(const int tileIndex);
	// Get empty tile to intentionally miss
	bool getTileIsEmpty(const int tileIndex);
	ShipTypeEnum getShipByTile(const int tileIndex);
	int getDimensions();
	int getTotalTiles();

	void checkMouseOver(const sf::Vector2f position, const int shipType, const bool shipHorizontal);
	TileStateEnum checkFiredPosition(const sf::Vector2f mousePosition);
	TileStateEnum checkFiredTileIndex(const int tileIndex);
	bool clickedInGrid(float xPos, float yPos);
	int calculateOffset(const int index, const bool shipHorizontal, const int dimensions);
	bool isWithinBoardSize(const int index);
	sf::Vector2f getRectangleShapePosition(const int index);

private:
	const int dimensions;
	const float widthPercentage;
	const float heightPercentage;	
	sf::RectangleShape boardRect;
	std::vector<int> board;
	TextureManager* textureManager;
	std::vector<sf::RectangleShape> tiles;
};