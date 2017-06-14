#include <fstream>
#include <iostream>

#include "DiggersGold.h"

void Read(std::ifstream &input, std::vector<short> &gold, int &sum);
void Write(std::ofstream &output, const std::vector<short> &items = {});

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		int sum = 0;
		std::vector<short> gold;
		Read(input, gold, sum);

		if (sum % 3 != 0)
		{
			Write(output);
			return 0;
		}

		CDiggersGold diggersGold(gold, sum / 3);
		Write(output, diggersGold.GetResult());
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void Write(std::ofstream &output, const std::vector<short> &items)
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

void Read(std::ifstream &input, std::vector<short> &gold, int &sum)
{
	int goldCount;
	sum = 0;
	input >> goldCount;

	while (goldCount > 0)
	{
		int goldWeight;
		input >> goldWeight;
		gold.push_back(goldWeight);
		sum += goldWeight;
		goldCount--;
	}
}