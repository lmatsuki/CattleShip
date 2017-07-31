#include "Settings.h"

Settings::Settings() : difficulty(Easy)
{

}

DifficultyEnum Settings::getDifficulty()
{
	return difficulty;
}

void Settings::setDifficulty(const DifficultyEnum newDifficulty)
{
	difficulty = newDifficulty;
}

