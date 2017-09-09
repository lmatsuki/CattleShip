#pragma once

#include <SFML\Audio.hpp>
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

	//sf::Font titleFont;
	sf::Font menuFont;

	//sf::Text titleText;
	//sf::Text playText;
	//sf::Text optionsText;
	//sf::Text quitText;
	sf::Sprite playSprite;
	sf::Sprite optionsSprite;
	sf::Sprite quitSprite;

	//sf::Text settingsText;
	//sf::Text easyText;
	//sf::Text mediumText;
	//sf::Text hardText;
	//sf::Text backText;	

	sf::Sprite settingsSprite;
	sf::Sprite backSprite;
	sf::Sprite easySprite;
	sf::Sprite mediumSprite;
	sf::Sprite hardSprite;

	sf::Sprite backgroundSprite;
	sf::Sprite titleSprite;

	// Music
	sf::Music menuTheme;

private:
	bool initialized;
	bool displaySettings;
	bool starting;
};