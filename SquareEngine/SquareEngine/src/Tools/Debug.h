#pragma once
#include <iostream>
#include <string>

namespace Square
{
	inline void Log(auto txt) { std::cout << txt << std::endl; };
	inline void Log(std::string txt) { std::cout << txt << std::endl; };
}