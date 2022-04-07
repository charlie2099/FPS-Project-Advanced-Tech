#pragma once
#include <chrono>
class Time
{
public:
	Time();
	void Update();
	float DT();
	float Elapsed();

private:
	std::chrono::steady_clock::time_point now;
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point startTime;
};
