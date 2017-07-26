#pragma once

#include <SFML/Graphics.hpp>
#include "SpriteEnum.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void LoadTextures();
	sf::Sprite GetSpriteBySpriteType(const SpriteEnum spriteType);
	sf::Sprite GetSpriteByShipType(const ShipTypeEnum shipType);
private:
	std::vector<sf::Texture>* textures;
};