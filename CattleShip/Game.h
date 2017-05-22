#pragma once

#include "GameStateEnum.h"

class Game
{
public:
	Game();

	void Init();
	void Start();
	void Render();

private:
	sf::Vector2f GetCenterOfScreen();
	float GetCenterOfText(sf::Text const &text);

	sf::RenderWindow window;
	sf::Font font;
	GameStateEnum gameState;
	sf::Color backGroundColor;
};
