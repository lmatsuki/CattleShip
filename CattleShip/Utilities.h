#pragma once

#include <SFML/Graphics.hpp>

namespace Utilities
{
	// Returns a Vector2f of the center point of the screen.
	sf::Vector2f getCenterOfScreen(const sf::RenderWindow& window);

	// Get the center x value of the text.
	float getCenterXOfText(const sf::RenderWindow& window, const sf::Text& text);

	// Render the text using all the parameters.
	void renderText(sf::Text& text, sf::RenderWindow& window, const std::string& textString,
		const sf::Font& font, int size, const sf::Uint32& style, const sf::Color& color,
		float xPos, float yPos);

	// Returns the full font directory path with the font name.
	std::string getFontPath(const std::string& fontName);

	// Returns the full images directory path with the image name.
	std::string getImagesPath(const std::string& imageName);

	// Convert the passed in x,y indices of a board to an index.
	int convertIndicesToIndex(const int x, const int y, const int dimension);
}