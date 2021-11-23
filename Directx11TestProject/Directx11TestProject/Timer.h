#pragma once
#include <chrono>

class Timer
{
public:
	Timer();

	float Mark();
	float Peek() const;

	float TimeElapsed();

private:
	std::chrono::steady_clock::time_point start;
};