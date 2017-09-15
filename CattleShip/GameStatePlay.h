#pragma once

#include <SFML\Audio.hpp>
#include "Game.h"
#include "GameState.h"

class GameStatePlay : public GameState
{
public:
	GameStatePlay(Game* game);
	~GameStatePlay();

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

	void handleCurrentPlayerClick(const sf::Vector2f mousePosition);
	Player* getCurrentPlayer();
	Player* getOtherPlayer();
	void renderWinner(Player* player);

private:
	sf::Font labelFont;
	sf::Text labelText;

	sf::Sprite backgroundSprite;
	sf::Sprite playerTurnSprite;
	sf::Sprite enemyTurnSprite;
	sf::Sprite playerWinSprite;
	sf::Sprite enemyWinSprite;
	sf::Sprite shipFoundSprite;
	bool displayFoundShip;
	bool isGameOver;

	// Music
	sf::Music playTheme;
	sf::Music victoryTheme;
	sf::Music defeatTheme;

	// Sound
	sf::Sound sound;
	sf::SoundBuffer foundSoundBuffer;
	sf::SoundBuffer missedSoundBuffer;
};