#include "Effects.h"

Effects::Effects() : fading(false), fadeColor(sf::Color::Black)
{

}

Effects::~Effects()
{

}

void Effects::fadeIn(const float duration, sf::Color fadeColor)
{

}

void Effects::fadeOut(const float duration, sf::Color fadeColor)
{

}

void Effects::setFadeColor(const sf::Color color)
{
	fadeColor = color;
}
