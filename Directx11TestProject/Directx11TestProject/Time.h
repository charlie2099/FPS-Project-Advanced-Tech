#pragma once
#include <chrono>
class Time
{
public:
	Time();
	void Tick();
	float DeltaTime();
	float TimeElapsed();

private:
	std::chrono::steady_clock::time_point now;
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point starting;
};
