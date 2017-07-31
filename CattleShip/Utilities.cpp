#include "Utilities.h"

namespace Utilities
{
	// Returns a Vector2f of the center point of the screen.
	sf::Vector2f getCenterOfScreen(const sf::RenderWindow& window)
	{
		const sf::Vector2u centerOfScreen = window.getSize();
		return sf::Vector2f(centerOfScreen.x / 2, centerOfScreen.y / 2);
	}

	// Get the center x value of the text.
	float getCenterXOfText(const sf::RenderWindow& window, const sf::Text& text)
	{
		const float centerOfText = getCenterOfScreen(window).x - text.getLocalBounds().width / 2;
		return centerOfText;
	}

	// Render the text using all the parameters.
	void renderText(sf::Text& text, sf::RenderWindow& window, const std::string& textString,
		const sf::Font& font, int size, const sf::Uint32& style, const sf::Color& color,
		float xPos, float yPos)
	{
		text.setFont(font);
		text.setString(textString);
		text.setCharacterSize(size);
		text.setStyle(style);
		text.setFillColor(color);
		text.setPosition(xPos, yPos);
		window.draw(text);
	}

	// Prepare the text using all the parameters.
	void prepareText(sf::Text& text, const std::string& textString,
		const sf::Font& font, int size, const sf::Uint32& style, const sf::Color& color,
		float xPos, float yPos)
	{
		text.setFont(font);
		text.setString(textString);
		text.setCharacterSize(size);
		text.setStyle(style);
		text.setFillColor(color);
		text.setPosition(xPos, yPos);
	}

	// Color the first selected text while coloring other texts white.
	void selectDifficulty(sf::Text & selectedText, sf::Text & secondText, sf::Text & thirdText)
	{
		selectedText.setFillColor(sf::Color::Cyan);
		secondText.setFillColor(sf::Color::White);
		thirdText.setFillColor(sf::Color::White);
	}

	// Returns the full font directory path with the font name.
	std::string getFontPath(const std::string& fontName)
	{
		return "D:/Documents/Visual Studio 2017/Projects/CattleShip/CattleShip/font/" + fontName;
	}

	// Returns the full images directory path with the image name.
	std::string getImagesPath(const std::string& imageName)
	{
		return "D:/Documents/Visual Studio 2017/Projects/CattleShip/CattleShip/images/" + imageName;
	}

	int convertIndicesToIndex(const int x, const int y, const int dimension)
	{
		if (x < 0 || y < 0 || dimension < 0)
			return 0;

		return x + y * dimension;
	}
}