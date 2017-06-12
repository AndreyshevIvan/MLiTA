#include <fstream>
#include <iostream>

#include "ItemsSearch.h"

void Read(std::ifstream &input, std::vector<size_t> &gold, size_t &sum);
void Write(std::ofstream &output, const std::vector<size_t> &items);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		size_t sum = 0;
		std::vector<size_t> gold;
		Read(input, gold, sum);

		if (sum % 3 != 0)
		{
			Write(output, { 0 });
			return;
		}

		CItemsSearch search(gold);
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
	for (auto i = 0; i < items.size(); i++)
	{
		output << items[i];
		if (i != items.size() - 1) output << ' ';
	}

	output << std::endl;
}

void Read(std::ifstream &input, std::vector<size_t> &gold, size_t &sum)
{
	size_t goldCount;
	gold.clear();
	input >> goldCount;

	while (goldCount > 0)
	{
		size_t goldWeight;
		input >> goldWeight;
		gold.push_back(goldWeight);
		sum += goldWeight;
		goldCount--;
	}
}