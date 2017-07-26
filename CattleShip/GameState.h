#pragma once

class GameState
{
public:
	GameState(Game* game) : game(game) {};
	virtual void handleInput() = 0;
	virtual void update(const float dt) = 0;
	virtual void render(const float dt) = 0;
	virtual ~GameState() {};

	Game* game;
};