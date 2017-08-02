#pragma once

#include <SFML/Graphics.hpp>

class Effects
{
public:
	Effects();
	~Effects();

	void init(const sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	// Need general functions for fade in/out
	void setFadeProperies(const int frames, sf::Color newFadeColor = sf::Color::Transparent);
	void fadeIn(const int frames, const float duration);
	void fadeOut(const float duration, sf::Color fadeColor = sf::Color::Transparent);
	void setFadeColor(const sf::Color color);

private:
	sf::VertexArray quadScreen;
	sf::Color fadeColor;
	float frameCount;
	bool fading;
};