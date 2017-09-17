#include "SoundManager.h"

SoundManager::SoundManager()
{
	loadSounds();
}

SoundManager::~SoundManager()
{
}

void SoundManager::setSoundVolume(const float volume)
{
	sound.setVolume(volume);
}

void SoundManager::playSound(const SoundEnum sound)
{
	this->sound.setBuffer(soundBank[sound]);
	this->sound.play();
}

void SoundManager::loadSounds()
{
	sound.setVolume(40);
	sf::SoundBuffer soundBuffer;

	// Populate vector with empty sound buffers
	for (int i = 0; i < LastSoundBuffer; i++)
		soundBank.push_back(soundBuffer);

	soundBank[StartGameSoundBuffer].loadFromFile(Utilities::getSoundfilePath("startgame.wav"));
	soundBank[ButtonClickSoundBuffer].loadFromFile(Utilities::getSoundfilePath("buttonclick.wav"));
	soundBank[SetDifficultySoundBuffer].loadFromFile(Utilities::getSoundfilePath("setdifficulty.wav"));
	soundBank[ToggleSoundBuffer].loadFromFile(Utilities::getSoundfilePath("toggleHorizontal.ogg"));
	soundBank[PlacedSoundBuffer].loadFromFile(Utilities::getSoundfilePath("placed.wav"));
	soundBank[FoundSoundBuffer].loadFromFile(Utilities::getSoundfilePath("found.wav"));
	soundBank[MissedSoundBuffer].loadFromFile(Utilities::getSoundfilePath("missed.wav"));
}
