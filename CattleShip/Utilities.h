#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SpriteEnum.h"

namespace Utilities
{
	// Returns a Vector2f of the center point of the screen.
	sf::Vector2f getCenterOfScreen(const sf::RenderWindow& window);

	// Get the center x value of the text.
	float getCenterXOfText(const sf::RenderWindow& window, const sf::Text& text);

	// Get the center x value of the sprite.
	float getCenterXOfSprite(const sf::RenderWindow& window, const sf::Sprite& sprite);

	// Render the text using all the parameters.
	void renderText(sf::Text& text, sf::RenderWindow& window, const std::string& textString,
		const sf::Font& font, int size, const sf::Uint32& style, const sf::Color& color,
		float xPos, float yPos);

	// Prepare the text using all the parameters.
	void prepareText(sf::Text& text, const std::string& textString,
		const sf::Font& font, int size, const sf::Uint32& style, const sf::Color& color,
		float xPos, float yPos);

	// Color the first selected text while coloring other texts white.
	void selectDifficulty(sf::Sprite& easySprite, sf::Sprite& mediumSprite, sf::Sprite& hardSprite, 
		SpriteEnum selected, TextureManager* textureManager, sf::RenderWindow* window);
	/*void selectDifficulty(sf::Text& selectedText, sf::Text& secondText, sf::Text& thirdText);*/

	// Returns the full font directory path with the font name.
	std::string getFontPath(const std::string& fontName);

	// Returns the full images directory path with the image name.
	std::string getImagesPath(const std::string& imageName);

	// Returns the full sounds directory path with the soundfile name.
	std::string getSoundfilePath(const std::string& soundfileName);

	// Convert the passed in x,y indices of a board to an index.
	int convertIndicesToIndex(const int x, const int y, const int dimension);

	// Clamp function for floats.
	float clamp(float n, float lo, float hi);
}