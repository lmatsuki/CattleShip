#include "Utilities.h"

namespace Utilities
{
	const std::string RESOURCE_PATH = "D:/Documents/Visual Studio 2017/Projects/CattleShip/CattleShip/";

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

	// Get the center x value of the sprite.
	float getCenterXOfSprite(const sf::RenderWindow & window, const sf::Sprite & sprite)
	{
		const float centerOfText = getCenterOfScreen(window).x - sprite.getLocalBounds().width / 2;
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
	void selectDifficulty(sf::Sprite& easySprite, sf::Sprite& mediumSprite, sf::Sprite& hardSprite, SpriteEnum selected, 
		TextureManager* textureManager, sf::RenderWindow* window)
	{
		const float centerHeight = Utilities::getCenterOfScreen(*window).y;
		easySprite = textureManager->GetSpriteBySpriteType(MenuEasy);
		mediumSprite = textureManager->GetSpriteBySpriteType(MenuMedium);
		hardSprite = textureManager->GetSpriteBySpriteType(MenuHard);

		switch (selected)
		{
		case MenuEasySelected:		easySprite = textureManager->GetSpriteBySpriteType(MenuEasySelected); break;
		case MenuMediumSelected:	mediumSprite = textureManager->GetSpriteBySpriteType(MenuMediumSelected); break;
		case MenuHardSelected:		hardSprite = textureManager->GetSpriteBySpriteType(MenuHardSelected); break;
		}

		easySprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(*window, easySprite) - 200, centerHeight));
		mediumSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(*window, mediumSprite), centerHeight));
		hardSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(*window, hardSprite) + 200, centerHeight));
	}

	//void selectDifficulty(sf::Text & selectedText, sf::Text & secondText, sf::Text & thirdText)
	//{
	//	selectedText.setFillColor(sf::Color::Green);
	//	secondText.setFillColor(sf::Color::White);
	//	thirdText.setFillColor(sf::Color::White);
	//}

	// Returns the full font directory path with the font name.
	std::string getFontPath(const std::string& fontName)
	{
		return RESOURCE_PATH + "font/" + fontName;
	}

	// Returns the full images directory path with the image name.
	std::string getImagesPath(const std::string& imageName)
	{
		return RESOURCE_PATH + "images/" + imageName;
	}

	std::string getSoundfilePath(const std::string& soundfileName)
	{
		return RESOURCE_PATH + "sounds/" +	soundfileName;
	}

	int convertIndicesToIndex(const int x, const int y, const int dimension)
	{
		if (x < 0 || y < 0 || dimension < 0)
			return 0;

		return x + y * dimension;
	}

	float clamp(float n, float lo, float hi)
	{
		return std::max(lo, std::min(n, hi));
	}
}