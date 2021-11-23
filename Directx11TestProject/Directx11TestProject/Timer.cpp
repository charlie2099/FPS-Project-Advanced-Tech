#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
	start = steady_clock::now();
}

float Timer::Mark()
{
	const auto last = start;
	start = steady_clock::now();
	const duration<float> frameTime = start - last;
	return frameTime.count();
}

float Timer::Peek() const
{
	return duration<float>(steady_clock::now() - start).count();
}

float Timer::TimeElapsed()
{
	auto now = steady_clock::now();
	return duration_cast<seconds>(now - start).count();
}
