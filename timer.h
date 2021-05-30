#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
	Timer();
	void reset();
	float elapsed();

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<float, std::ratio<1>> second_;
	std::chrono::time_point<clock_> beg_;
};

#endif