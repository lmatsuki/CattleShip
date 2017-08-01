#pragma once

#include <SFML/Graphics.hpp>

class Effects
{
public:
	Effects();
	~Effects();

	// Need general functions for fade in/out
	void fadeIn(const float duration, sf::Color fadeColor = sf::Color::Transparent);
	void fadeOut(const float duration, sf::Color fadeColor = sf::Color::Transparent);
	void setFadeColor(const sf::Color color);

private:
	sf::Color fadeColor;
	bool fading;
};