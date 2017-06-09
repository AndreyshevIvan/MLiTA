#include <vector>
#include <fstream>
#include <iostream>

#include "BigNumber.h"

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ifstream output("output.txt");
		(void)output;

		CBigNumber first;
		CBigNumber second;
		Read(input, first, second);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second)
{
	std::string numberStr;
	getline(input, numberStr);
	first = CBigNumber(numberStr);
	getline(input, numberStr);
	second = CBigNumber(numberStr);
}