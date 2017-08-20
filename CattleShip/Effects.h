#pragma once

#include <time.h>
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "TweenEnum.h"
#include "Utilities.h"
#include "FadeEnum.h"
#include "TimerGroup.h"

# define M_PI           3.14159265358979323846  /* pi */

class Effects
{
public:
	Effects();
	~Effects();

	void init(const sf::RenderWindow& window);
	void update(const float dt);
	void render(sf::RenderWindow& window);

	void startFade(const float newDuration, const TweenEnum tweenState, const sf::Color newFadeColor = sf::Color::Transparent, 
		const float newPauseDuration = 0, const FadeEnum newFadeDirection = FadeOut);
	float getTweenValue(const float time, const float begin, const float change, const float duration, const TweenEnum tweenType);
	std::string getElapsedTime();
	std::string getCurrentAlpha();
	float getPauseStartTime();
	float getPauseEndTime();
	bool isFading();
	void setBackgroundColor(const sf::Color color);
	void setQuadColor();
	void setQuadPositionFullScreen(const int width, const int height);
	
	TimerGroup timers;

private:
	sf::VertexArray quadScreen;
	sf::Color fadeColor;
	TweenEnum tween;
	FadeEnum fadeDirection;
	float duration;
	float elapsedTime;
	float pauseDuration;
	std::clock_t clockBegin;
	bool fading;	
};