#pragma once

int MainFunction(int argc, char** argv)
{
	return Application(argc, argv);
}

int main(int argc, char** argv)
{
	return MainFunction(argc, argv);
}
