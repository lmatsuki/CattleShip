#pragma once

#include <stack>
#include "Board.h"
#include "TextureManager.h"
#include "Player.h"
#include "AI.h"
#include "Settings.h"
#include "Effects.h"
#include "SoundManager.h"

class GameState;

class Game
{
public:
	Game();
	~Game();

	void init();
	void gameLoop();	
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	sf::RenderWindow window;
	std::stack<GameState*> states;
	Player playerOne;
	Player playerTwo;
	bool playerTurn;
	TextureManager textureManager;
	Settings settings;
	AI ai;

	// DEBUG
	void printCoordinates(int x, int y);
	void printText(const std::string& text);
	sf::Text coordText;

	Effects effects;
	SoundManager soundManager;
private:	
	sf::Color backGroundColor;
	sf::Font font;
};
