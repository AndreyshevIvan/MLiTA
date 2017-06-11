#include <vector>
#include <fstream>
#include <iostream>

void Read(std::ifstream &input, std::vector<size_t> &gold, size_t &sum);
size_t CalcResult(const std::vector<size_t> &gold, size_t fullWeight);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		size_t sum;
		std::vector<size_t> gold;
		Read(input, gold, sum);

		output << CalcResult(gold, sum);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

size_t CalcResult(const std::vector<size_t> &gold, size_t fullWeight)
{
	(void)gold;
	(void)fullWeight;

	return 0;
}

void Read(std::ifstream &input, std::vector<size_t> &gold, size_t &sum)
{
	size_t goldCount;
	input >> goldCount;
	sum = 0;

	while (goldCount > 0)
	{
		size_t goldWeight;
		input >> goldWeight;
		gold.push_back(goldWeight);
		sum += goldWeight;
		goldCount--;
	}
}