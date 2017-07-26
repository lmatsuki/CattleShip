#include "Player.h"
#include "ShipTypeEnum.h"
#include "Utilities.h"

Player::Player(const int dimension, TextureManager* textureManager) :
	board(dimension, textureManager), textureManager(textureManager), currentShipSelection(None)
{
	
}

void Player::init()
{
	currentShipSelection = FirstShip;
}

void Player::renderCurrentShip(sf::RenderWindow & window)
{
	if (currentShipSelection >= FirstShip && currentShipSelection <= LastShip)
	{
		sf::Sprite sprite = textureManager->GetSpriteByShipType((ShipTypeEnum)currentShipSelection);
		if (currentShipSelection != Carrier)
			sprite.setPosition(sf::Vector2f(Utilities::getCenterOfScreen(window).x - (sprite.getTextureRect().width / 2), 10));
		else
			sprite.setPosition(sf::Vector2f(Utilities::getCenterOfScreen(window).x - (sprite.getTextureRect().width / 2), 60));
		window.draw(sprite);
	}
}
