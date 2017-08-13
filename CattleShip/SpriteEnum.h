#pragma once

#include "ShipTypeEnum.h"

enum SpriteEnum
{
	SpriteGrass = LastShip + 1,
	MenuBackground,
	MenuTitle,
	MenuPlay,
	MenuOptions,
	MenuExit,
	MenuSettings,
	MenuBack,
	MenuEasy,
	MenuEasySelected,
	MenuMedium,
	MenuMediumSelected,
	MenuHard,
	MenuHardSelected,
	PlacementLabel,
	BoardBackgroundSprite,
	PlayPlayerTurnSprite,
	PlayEnemyTurnSprite,
	PlayPlayerWinSprite,
	PlayEnemyWinSprite,
	HitShip,
	MissedShip,
	LastSprite = MissedShip + 1,
};