#pragma once

#include <vector>
#include <SFML\Audio.hpp>
#include "SoundEnum.h"
#include "Utilities.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void setSoundVolume(const float volume);
	void playSound(const SoundEnum sound);
	void loadSounds();

private:
	sf::Sound sound;
	std::vector<sf::SoundBuffer> soundBank;
};