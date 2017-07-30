#pragma once

#include "DifficultyEnum.h"

class Settings
{
public:
	Settings();
	DifficultyEnum getDifficulty();

private:
	DifficultyEnum difficulty;
};