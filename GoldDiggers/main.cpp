#include <vector>
#include <fstream>
#include <iostream>

void Read(std::ifstream &input, std::vector<size_t> &gold);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ifstream output("output.txt");
		(void)output;

		std::vector<size_t> gold;
		Read(input, gold);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void Read(std::ifstream &input, std::vector<size_t> &gold)
{
	size_t goldCount;
	input >> goldCount;

	while (goldCount > 0)
	{
		size_t goldWeight;
		input >> goldWeight;
		gold.push_back(goldWeight);
		goldCount--;
	}
}