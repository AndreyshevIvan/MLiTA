#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

size_t func(int ladderSize, int stepSize);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		size_t ladderSize = 0;
		size_t stepSize = 0;
		input >> ladderSize >> stepSize;

		auto count = func(ladderSize, stepSize);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

size_t func(int ladderSize, int stepSize)
{
	if (ladderSize < 1)
	{
		return 0;
	}

	if (ladderSize == 1)
	{
		return 1;
	}

	size_t result = (ladderSize - stepSize <= 0) ? 1 : 0;

	for (auto i = ladderSize - 1; i >= ladderSize - stepSize; i--)
	{
		result += func(i, stepSize);
	}

	return result;
}