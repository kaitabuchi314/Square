#include "Timer.h"

namespace Square
{
	void Timer::Start()
	{
		isRunning = true;
		beginTime = window->GetTime();
	}
	
	void Timer::Stop()
	{
		isRunning = false;
		endTime = window->GetTime();
	}

	double Timer::GetMilliseconds()
	{
		return (endTime - beginTime) * 1000;
	}

	bool Timer::IsRunning()
	{
		return isRunning;
	}

	Timer::operator double()
	{
		return GetMilliseconds();
	}

	Timer::operator bool()
	{
		return IsRunning();
	}
}
