#include <vector>
#include <fstream>
#include <iostream>

#include "BigNumber.h"

void Read(std::ifstream &input, CBigNumber &first);
void Calc(const CBigNumber &first, const CBigNumber &second);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ifstream output("output.txt");
		(void)output;

		CBigNumber ticket;
		Read(input, ticket);

		CBigNumber zero;

		auto minus = ticket - zero;
		(void)minus;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void Read(std::ifstream &input, CBigNumber &number)
{
	std::string numberStr;
	getline(input, numberStr);
	getline(input, numberStr);
	number = CBigNumber(numberStr);
}

void Calc(const CBigNumber &first, const CBigNumber &second)
{
	(void)first;
	(void)second;
}