#include "Settings.h"

Settings::Settings() : difficulty(Medium), volume(40), currentVolume(0), volumeIncrement(0.4)
{

}

DifficultyEnum Settings::getDifficulty()
{
	return difficulty;
}

float Settings::getCurrentVolume()
{
	return currentVolume;
}

float Settings::getVolume()
{
	return volume;
}

void Settings::setDifficulty(const DifficultyEnum newDifficulty)
{
	difficulty = newDifficulty;
}

void Settings::setVolume(const float volume)
{
	this->volume = volume;
}

void Settings::setCurrentVolume(const float volume)
{
	this->currentVolume = volume;
}

bool Settings::adjustedVolume()
{
	const int currentVolumeInt = (int)(currentVolume * 100);
	const int volumeInt = volume * 100;
	if (currentVolumeInt == volumeInt)
		return false;

	if (currentVolume < volume)
		currentVolume += volumeIncrement;
	else if (currentVolume > volume)
		currentVolume -= volumeIncrement;
	return true;
}

