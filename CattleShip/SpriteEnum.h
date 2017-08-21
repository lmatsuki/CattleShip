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
	RotateSprite,
	PlayPlayerTurnSprite,
	PlayEnemyTurnSprite,
	PlayPlayerWinSprite,
	PlayEnemyWinSprite,
	FoundShip,
	HitShip,
	MissedShip,
	LastSprite = MissedShip + 1,
};