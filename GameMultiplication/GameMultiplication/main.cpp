#include "Game.h"

namespace
{
	const std::string INPUT_FILE = "input.txt";
	const std::string OUTPUT_FILE = "output.txt";
}

int main()
{
	try
	{
		CGame multiplicationGame(INPUT_FILE);
		multiplicationGame.Start();
		multiplicationGame.PrintResults(OUTPUT_FILE);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		return 1;
	}

	return 0;
}