#include "TimerGroup.h"

TimerGroup::~TimerGroup()
{
	while (!timerGroup.empty())
		timerGroup.pop_back();
}

void TimerGroup::init()
{
	Timer newTimer;
	// Get the last value + 1 as the count and add timers to the list
	for (int i = 0; i < LastTimerEnum; i++)
	{		
		timerGroup.push_back(newTimer);
	}
}

void TimerGroup::startTimer(const TimerEnum timerEnum, const float newDuration)
{
	timerGroup.at((int)timerEnum).start(newDuration);
}

bool TimerGroup::timerHasFinished(const TimerEnum timerEnum, const float elapsedTime)
{
	return timerGroup.at((int)timerEnum).hasFinished(elapsedTime);
}

bool TimerGroup::timerIsReady(const TimerEnum timerEnum)
{
	return timerGroup.at((int)timerEnum).isReady();
}
