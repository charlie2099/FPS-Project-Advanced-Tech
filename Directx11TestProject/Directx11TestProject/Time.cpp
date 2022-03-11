#include "Time.h"

Time::Time()
{
	now = std::chrono::steady_clock::now();
	last = now;
	starting = now;
}

void Time::Tick()
{
	last = now;
	now = std::chrono::steady_clock::now();
}

float Time::DeltaTime()
{
	const std::chrono::duration<float> delta = now - last;
	return delta.count();
}

float Time::TimeElapsed()
{
	const std::chrono::duration<float> delta = now - starting;
	return delta.count();
}