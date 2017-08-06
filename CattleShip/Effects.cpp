#include "Effects.h"

Effects::Effects() : fading(false), fadeColor(sf::Color::Black), 
	duration(0), clockBegin(0), pauseDuration(0)
{
	
}

Effects::~Effects()
{

}

void Effects::init(const sf::RenderWindow& window)
{
	int width = window.getSize().x;
	int height = window.getSize().y;

	quadScreen.setPrimitiveType(sf::PrimitiveType::Quads);
	quadScreen.resize(4);
	quadScreen[0].position = sf::Vector2f(0, 0);
	quadScreen[1].position = sf::Vector2f(0, height);
	quadScreen[2].position = sf::Vector2f(width, height);
	quadScreen[3].position = sf::Vector2f(width, 0);

	quadScreen[0].color = sf::Color::Transparent;
	quadScreen[1].color = sf::Color::Transparent;
	quadScreen[2].color = sf::Color::Transparent;
	quadScreen[3].color = sf::Color::Transparent;
}

void Effects::update(const float dt)
{	
	if (fading)
	{
		float currentTime = std::clock() / (float)CLOCKS_PER_SEC;
		elapsedTime = (std::clock() - clockBegin) / (float)CLOCKS_PER_SEC;
		if (duration + pauseDuration > elapsedTime)
		{
			fadeColor.a = getTweenValue(elapsedTime, 0, 255, duration, tween);
			quadScreen[0].color = fadeColor;
			quadScreen[1].color = fadeColor;
			quadScreen[2].color = fadeColor;
			quadScreen[3].color = fadeColor;
		}
		else
		{
			duration = 0;
			fading = false;
			pauseDuration = 0;
		}
	}
}

void Effects::render(sf::RenderWindow & window)
{
	window.draw(quadScreen);
}

void Effects::startFade(const float newDuration, const TweenEnum tweenState, const sf::Color newFadeColor,
	const float newPauseDuration)
{
	fading = true;
	clockBegin = std::clock();
	fadeColor = newFadeColor;
	tween = tweenState;
	duration = newDuration;
	pauseDuration = newPauseDuration;
}

float Effects::getTweenValue(const float time, const float begin, const float change, const float duration,
	const TweenEnum tweenType)
{
	float t = time / duration;
	switch (tweenType)
	{
	case Linear:
		return change * t + begin;
	case QuadEaseIn:
		return change * t * t + begin;
	case QuadEaseOut:
		return -change * t * (t - 2) + begin;
	case CubicEaseIn:
		return change * t * t * t + begin;
	case CubicEaseOut:
		t--;
		return change * (t * t * t + 1) + begin;
	case SineEaseIn:
		return -change * cos(t * (M_PI / 2)) + change + begin;
	case SineEaseOut:
		return change * sin(t * (M_PI / 2)) + begin;
	case SineEaseInOut:
		if (time < getPauseStartTime())		// Fade in
			return 255 - getTweenValue(time * 2, begin, change, duration, SineEaseIn);
		else if (time > getPauseEndTime())  // Fade out
			return 255 - getTweenValue((time - 1) * 2, begin, change, duration, SineEaseOut);
		else								// Pause delay
			return 0;
	default:
		return 0;
	}
}

std::string Effects::getElapsedTime()
{
	return std::to_string(elapsedTime);
}

std::string Effects::getCurrentAlpha()
{
	return std::to_string(fadeColor.a);
}

float Effects::getPauseStartTime()
{
	return duration / 2.0f;
}

float Effects::getPauseEndTime()
{
	return getPauseStartTime() + pauseDuration;
}