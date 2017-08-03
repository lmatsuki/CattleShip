#include "Effects.h"

Effects::Effects() : fading(false), fadeColor(sf::Color::Black), frameCount(0)
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

void Effects::update()
{
	if (frameCount > 0)
	{
		switch (tween)
		{
		case In:
			fadeColor.a = fadeColor.a <= 0 ? 0 : fadeColor.a - 1;
			break;
		case Out:
			fadeColor.a = fadeColor.a >= 255 ? 255 : fadeColor.a + 1;
			break;
		}
		
		quadScreen[0].color = fadeColor;
		quadScreen[1].color = fadeColor;
		quadScreen[2].color = fadeColor;
		quadScreen[3].color = fadeColor;
		frameCount--;
	}
}

void Effects::render(sf::RenderWindow & window)
{
	window.draw(quadScreen);
}

void Effects::startFade(const int frames, TweenEnum tweenState, sf::Color newFadeColor)
{
	fading = true;
	fadeColor = newFadeColor;
	tween = tweenState;
	frameCount = frames;
}

void Effects::setFadeProperies(const int frames, sf::Color newFadeColor)
{
	if (!fading)
	{
		frameCount = frames;
		fadeColor = newFadeColor;
	}
}

void Effects::fadeIn(const int frames, const float duration)
{
	if (frameCount > 0)
	{
		frameCount--;
		quadScreen[0].color = fadeColor;
		quadScreen[2].color = fadeColor;
	}
	else
	{
		quadScreen[0].color = sf::Color::Transparent;
		quadScreen[2].color = sf::Color::Transparent;
	}
}

void Effects::fadeOut(const float duration, sf::Color fadeColor)
{

}

void Effects::setFadeColor(const sf::Color color)
{
	fadeColor = color;
}
