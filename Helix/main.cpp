#include "Helix.h"

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	int helixSize;
	input >> helixSize;

	try
	{
		CHelix helix(helixSize);
		helix.Print(output);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		return 1;
	}

	return 0;
}