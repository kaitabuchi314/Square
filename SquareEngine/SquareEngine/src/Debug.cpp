#include "Debug.h"
#include <iostream>

void Square::Log(std::string txt)
{
	std::cout << txt << std::endl;
}

void Square::Log(const char* txt)
{
	std::cout << txt << std::endl;
}

void Square::Log(float txt)
{
	std::cout << txt << std::endl;
}

void Square::Log(int txt)
{
	std::cout << txt << std::endl;
}
