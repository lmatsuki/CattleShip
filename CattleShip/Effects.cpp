#include "Effects.h"

Effects::Effects() : fading(false), fadeColor(sf::Color::Black), 
	duration(0), clockBegin(0)
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
		if (duration > elapsedTime)
		{
			float tweenValue = Utilities::clamp((elapsedTime / duration) * 255, 0.0f, 255.0f);
			fadeColor.a = getTweenValue(elapsedTime, 0, 255, duration);

			quadScreen[0].color = fadeColor;
			quadScreen[1].color = fadeColor;
			quadScreen[2].color = fadeColor;
			quadScreen[3].color = fadeColor;
		}
		else
		{
			duration = 0;
			fading = false;
		}
	}
}

void Effects::render(sf::RenderWindow & window)
{
	window.draw(quadScreen);
}

void Effects::startFade(const float newDuration, TweenEnum tweenState, sf::Color newFadeColor)
{
	fading = true;
	clockBegin = std::clock();
	fadeColor = newFadeColor;
	tween = tweenState;
	duration = newDuration;
}

float Effects::getTweenValue(const float time, const float begin, const float change, const float duration)
{
	float t = time / duration;
	switch (tween)
	{
	case Linear:
		return change * time / duration + begin;// = tweenValue * clock() / duration;
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
		return -change * cos(time / duration * (M_PI / 2)) + change + begin;
	case SineEaseOut:
		return change * sin(time / duration * (M_PI / 2)) + begin;
	default:
		return 0;
	}
}

std::string Effects::getElapsedTime()
{
	return std::to_string(elapsedTime);
}
