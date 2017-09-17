#pragma once

#include "DifficultyEnum.h"

class Settings
{
public:
	Settings();
	
	DifficultyEnum getDifficulty();
	float getCurrentVolume();
	float getVolume();

	virtual void setDifficulty(const DifficultyEnum newDifficulty);
	virtual void setVolume(const float volume);
	virtual void setCurrentVolume(const float volume);
	virtual bool adjustedVolume();

private:
	DifficultyEnum difficulty;
	float volume;
	float currentVolume;
	float volumeIncrement;
};