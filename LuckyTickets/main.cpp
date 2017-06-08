#include <vector>
#include <fstream>
#include <iostream>

#include "BigNumber.h"

CBigNumber Read(std::ifstream &input);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ifstream output("output.txt");
		(void)output;

		auto ticketNumber = Read(input);
		(void)ticketNumber;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

CBigNumber Read(std::ifstream &input)
{
	std::string numberStr;
	getline(input, numberStr);
	getline(input, numberStr);
	return CBigNumber(numberStr);
}