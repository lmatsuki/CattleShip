#include "TextureManager.h"
#include "Utilities.h"

TextureManager::TextureManager()
{
	textures = new std::vector<sf::Texture>();
	LoadTextures();
}

TextureManager::~TextureManager()
{
	delete textures;
}

void TextureManager::LoadTextures()
{
	sf::Texture texture;

	for (int i = 0; i < LastSprite; i++)
		textures->push_back(texture);

	texture.loadFromFile(Utilities::getImagesPath("grass.png"), sf::IntRect(0, 0, 640, 480));
	textures->at(SpriteGrass) = texture;
	texture.loadFromFile(Utilities::getImagesPath("pig_walk.png"), sf::IntRect(0, 128, 128, 128));
	textures->at(Cruiser) = texture;
	texture.loadFromFile(Utilities::getImagesPath("chicken_walk.png"), sf::IntRect(0, 32, 32, 32));
	textures->at(Carrier) = texture;
	texture.loadFromFile(Utilities::getImagesPath("sheep_walk.png"), sf::IntRect(0, 128, 128, 128));
	textures->at(Battleship) = texture;
	texture.loadFromFile(Utilities::getImagesPath("llama_walk.png"), sf::IntRect(0, 128, 128, 128));
	textures->at(Submarine) = texture;
	texture.loadFromFile(Utilities::getImagesPath("cow_walk.png"), sf::IntRect(0, 128, 128, 128));
	textures->at(Destroyer) = texture;
	texture.loadFromFile(Utilities::getImagesPath("hit.png"), sf::IntRect(0, 0, 128, 128));
	textures->at(HitShip) = texture;
	texture.loadFromFile(Utilities::getImagesPath("missed.png"), sf::IntRect(0, 0, 128, 128));
	textures->at(MissedShip) = texture;
	texture.loadFromFile(Utilities::getImagesPath("cattleship-bg.png"), sf::IntRect(0, 0, 800, 600));
	textures->at(MenuBackground) = texture;
}

sf::Sprite TextureManager::GetSpriteBySpriteType(const SpriteEnum spriteType)
{
	sf::Sprite sprite;
	sprite.setTexture(textures->at(spriteType));
	return sprite;
}

sf::Sprite TextureManager::GetSpriteByShipType(const ShipTypeEnum shipType)
{
	sf::Sprite sprite;
	sprite.setTexture(textures->at(shipType));
	return sprite;
}


