#include <fstream>
#include <iostream>

#include "DiggersGold.h"

void Read(std::ifstream &input, CDiggersGold &gold, size_t &sum);
void Write(std::ofstream &output, const std::vector<size_t> &items = {});

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		size_t sum = 0;
		CDiggersGold gold;
		Read(input, gold, sum);

		if (sum % 3 != 0)
		{
			Write(output);
			return 0;
		}

		CDiggersGold search(gold);
		Write(output, search.GetEqualPack(sum / 3));
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void Write(std::ofstream &output, const std::vector<size_t> &items)
{
	output << items.size() << std::endl;
	if (items.size() == 0)
	{
		return;
	}

	for (size_t i = 0; i < items.size(); i++)
	{
		output << items[i];
		if (i != items.size() - 1) output << ' ';
	}

	output << std::endl;
}

void Read(std::ifstream &input, CDiggersGold &gold, size_t &sum)
{
	int goldCount;
	input >> goldCount;

	while (goldCount > 0)
	{
		int goldWeight;
		input >> goldWeight;
		gold.AddGold(goldWeight);
		sum += goldWeight;
		goldCount--;
	}
}