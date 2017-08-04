#pragma once

#include <time.h>
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "TweenEnum.h"
#include "Utilities.h"

# define M_PI           3.14159265358979323846  /* pi */

class Effects
{
public:
	Effects();
	~Effects();

	void init(const sf::RenderWindow& window);
	void update(const float dt);
	void render(sf::RenderWindow& window);

	// Need general functions for fade in/out
	void startFade(const float newDuration, TweenEnum tweenState, sf::Color newFadeColor = sf::Color::Transparent);
	float getTweenValue(const float time, const float begin, const float change, const float duration);
	std::string getElapsedTime();

private:
	sf::VertexArray quadScreen;
	sf::Color fadeColor;
	TweenEnum tween;
	float duration;
	float elapsedTime;
	std::clock_t clockBegin;
	bool fading;
};