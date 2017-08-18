#include "Timer.h"

Timer::Timer() : ready(true), duration(0)
{

}

Timer::~Timer()
{
}

// Update the duration with elapsed time from clock,
// then return whether the duration is <= 0.
bool Timer::hasFinished(const float elapsedTime)
{
	duration -= elapsedTime;

	if (duration <= 0)
	{
		reset();
		return true;
	}
		
	return false;
}

void Timer::start(const float newDuration)
{
	if (ready)
	{
		duration = newDuration;		
		ready = false;
	}
}

void Timer::reset()
{
	duration = 0;
	ready = true;
}

bool Timer::isReady()
{
	return ready;
}
