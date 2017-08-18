#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	// Whether the timer has elapsed the duration.
	bool hasFinished(const float elapsedTime);

	void start(const float newDuration);

	// Allow the timer to be started again.
	void reset();

	// Whether the timer is ready.
	bool isReady();

private:
	bool ready;
	float duration;
};