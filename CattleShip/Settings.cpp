#include "Settings.h"

Settings::Settings() : difficulty(Easy)
{

}

DifficultyEnum Settings::getDifficulty()
{
	return difficulty;
}

