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
	void render(sf::RenderWindow& window);
	void renderShip(const int shipType, const sf::Vector2f position, sf::RenderWindow& window);

	void setBoardPosition(const sf::RenderWindow& window);
	void setBoardSize(const sf::RenderWindow& window);
	void setBoardFillColor(const sf::Color color);
	void setBoardPiece(const int boardIndex, const int shipType, const bool shipHorizontal);
	void clearOutlineColors();

	int getTileByCoords(const sf::Vector2f mousePosition);
	int getValidTileByCoords(const sf::Vector2f mousePosition, const int shipType, const bool shipHorizontal);
	bool getIsValidTileByIndex(const int tilePosition, const int shipSize, const bool shipHorizontal);
	int getDimensions();

	/*void checkClickedTile(bool playerTurn, const sf::Vector2f position);
	void checkPlacedTile(const sf::Vector2f position);*/
	void checkMouseOver(const sf::Vector2f position, const int shipType, const bool shipHorizontal);
	TileStateEnum checkFiredPosition(const sf::Vector2f mousePosition);
	bool clickedInGrid(float xPos, float yPos);
	void updateHit(bool hit, bool playerTurn, int col, int row);	

private:
	const int dimensions;
	const float widthPercentage;
	const float heightPercentage;	
	sf::RectangleShape boardRect;
	std::vector<int> board;
	TextureManager* textureManager;
	std::vector<sf::RectangleShape> tiles;
};