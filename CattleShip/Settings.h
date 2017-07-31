#pragma once

#include "DifficultyEnum.h"

class Settings
{
public:
	Settings();
	
	DifficultyEnum getDifficulty();
	virtual void setDifficulty(const DifficultyEnum newDifficulty);

private:
	DifficultyEnum difficulty;
};