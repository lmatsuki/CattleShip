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

	// Animals - Tiles
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
	/*texture.loadFromFile(Utilities::getImagesPath("missed.png"), sf::IntRect(0, 0, 128, 128));*/
	texture.loadFromFile(Utilities::getImagesPath("missed.png"), sf::IntRect(0, 0, 128, 128));
	textures->at(MissedShip) = texture;

	// Main menu
	texture.loadFromFile(Utilities::getImagesPath("cattleship-bg.png"), sf::IntRect(0, 0, 800, 600));
	textures->at(MenuBackground) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-title.png"), sf::IntRect(0, 0, 400, 100));
	textures->at(MenuTitle) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-play.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuPlay) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-options.png"), sf::IntRect(0, 0, 200, 48));
	textures->at(MenuOptions) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-quit.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuExit) = texture;

	// Settings
	texture.loadFromFile(Utilities::getImagesPath("menu-settings.png"), sf::IntRect(0, 0, 224, 48));
	textures->at(MenuSettings) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-back.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuBack) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-easy.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuEasy) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-easy-selected.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuEasySelected) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-medium.png"), sf::IntRect(0, 0, 224, 48));
	textures->at(MenuMedium) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-medium-selected.png"), sf::IntRect(0, 0, 224, 48));
	textures->at(MenuMediumSelected) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-hard.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuHard) = texture;
	texture.loadFromFile(Utilities::getImagesPath("menu-hard-selected.png"), sf::IntRect(0, 0, 128, 48));
	textures->at(MenuHardSelected) = texture;

	// Board
	texture.loadFromFile(Utilities::getImagesPath("board-bg.png"), sf::IntRect(0, 0, 800, 600));
	textures->at(BoardBackgroundSprite) = texture;

	// Placement
	texture.loadFromFile(Utilities::getImagesPath("placement-label.png"), sf::IntRect(0, 0, 500, 100));
	textures->at(PlacementLabel) = texture;

	// Play
	texture.loadFromFile(Utilities::getImagesPath("play-yourturn.png"), sf::IntRect(0, 0, 264, 64));
	textures->at(PlayPlayerTurnSprite) = texture;
	texture.loadFromFile(Utilities::getImagesPath("play-enemyturn.png"), sf::IntRect(0, 0, 400, 64));
	textures->at(PlayEnemyTurnSprite) = texture;

	texture.loadFromFile(Utilities::getImagesPath("winner-player.png"), sf::IntRect(0, 0, 384, 72));
	textures->at(PlayPlayerWinSprite) = texture;
	texture.loadFromFile(Utilities::getImagesPath("winner-enemy.png"), sf::IntRect(0, 0, 384, 72));
	textures->at(PlayEnemyWinSprite) = texture;
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


