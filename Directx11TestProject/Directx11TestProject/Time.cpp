#include "Time.h"

Time::Time()
{
	now = std::chrono::steady_clock::now();
	last = now;
	startTime = now;
}

void Time::Update()
{
	last = now;
	now = std::chrono::steady_clock::now();
}

float Time::DT()
{
	const std::chrono::duration<float> delta = now - last;
	return delta.count();
}

float Time::Elapsed()
{
	const std::chrono::duration<float> delta = now - startTime;
	return delta.count();
}