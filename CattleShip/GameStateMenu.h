#pragma once

#include "Game.h"
#include "GameState.h"

class GameStateMenu : public GameState
{
public:
	GameStateMenu(Game* game);
	~GameStateMenu();

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

	virtual void initialize();
	// If it returns true, that means it must return (play was selected).
	virtual bool handleLeftClick(const int x, const int y);

	sf::Font titleFont;
	sf::Font menuFont;

	sf::Text titleText;
	sf::Text playText;
	sf::Text optionsText;
	sf::Text quitText;

	sf::Text settingsText;
	sf::Text easyText;
	sf::Text mediumText;
	sf::Text hardText;
	sf::Text backText;	

private:
	bool initialized;
	bool displaySettings;
};