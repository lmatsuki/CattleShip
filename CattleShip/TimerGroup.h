#pragma once

#include <vector>
#include "Timer.h"
#include "TimerEnum.h"

class TimerGroup
{
public:
	~TimerGroup();

	void init();
	void startTimer(const TimerEnum timerEnum, const float newDuration);
	bool timerHasFinished(const TimerEnum timerEnum, const float elapsedTime);
	bool timerIsReady(const TimerEnum timerEnum);
	

private:
	std::vector<Timer> timerGroup;
};