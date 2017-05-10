#include "Game.h"
#include "Exception.h"

namespace
{
	const std::string INPUT = "input.txt";
	const std::string OUTPUT = "output.txt";
}

int main()
{
	try
	{
		CGame multiplicationGame(INPUT);
		multiplicationGame.Start();
		multiplicationGame.PrintResults(OUTPUT);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		system("pause");
		return 1;
	}

	system("pause");
	return 0;
}