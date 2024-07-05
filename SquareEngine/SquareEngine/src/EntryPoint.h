#pragma once

int MainFunction(int argc, char** argv)
{
	return Entry(argc, argv);
}

int main(int argc, char** argv)
{
	return MainFunction(argc, argv);
}
