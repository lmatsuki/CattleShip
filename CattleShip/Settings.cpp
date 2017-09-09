#include "Settings.h"

Settings::Settings() : difficulty(Easy), volume(40), currentVolume(0), volumeIncrement(0.4)
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

void Settings::setDifficulty(const DifficultyEnum newDifficulty)
{
	difficulty = newDifficulty;
}

void Settings::setVolume(const float volume)
{
	this->volume = volume;
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

