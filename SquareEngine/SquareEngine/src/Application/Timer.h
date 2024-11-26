#pragma once
#include <Window.h>

namespace Square
{
	class Timer
	{
	public:
		inline Timer(Window* window) { this->window = window; };
		
		void Start();
		void Stop();
		
		double GetMilliseconds();
		bool IsRunning();

		operator double();
		operator bool();
	private:
		Window* window;
	private:
		double beginTime = 0;
		double endTime = 0;
		bool isRunning = false;
	};
}