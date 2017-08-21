#pragma once

enum TimerEnum
{
	PlayerOneTurnEnd,
	PlayerOneFiredMissle,
	PlayerFinishedPlacement,
	DelayAfterAIFadeOut,
	DelayAfterAIFires,
	LastTimerEnum = DelayAfterAIFires + 1
};