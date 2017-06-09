#include <vector>
#include <fstream>
#include <iostream>

#include "BigNumber.h"

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second);
size_t Calc(const CBigNumber &first, const CBigNumber &second);
size_t EasyCalc(size_t first, size_t second);

bool IsLucky(const CBigNumber &firstPart, const CBigNumber &secondPart);
bool IsLucky(size_t firstPart, size_t secondPart);

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

		//auto minus = first - second;
		//(void)minus;

		IsLucky(1337, 1400);
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
	std::string N;
	getline(input, N);
	std::string ticketStr;
	getline(input, ticketStr);

	std::string firstStr;
	std::string secondStr;

	for (size_t i = 0; i < std::stoi(N); i++)
	{
		firstStr += ticketStr[i];
		secondStr += ticketStr[i + std::stoi(N)];
	}

	first = CBigNumber(firstStr);
	second = CBigNumber(secondStr);
}

size_t Calc(const CBigNumber &first, const CBigNumber &second)
{
	(void)first;
	(void)second;
	return 0;
}

size_t EasyCalc(size_t first, size_t second)
{
	if (first == second)
	{
		return 0;
	}
	else if (first < second)
	{
		std::swap(first, second);
	}



	return 0;
}

bool IsLucky(const CBigNumber &firstPart, const CBigNumber &secondPart)
{
	return firstPart.DigitsSum() == secondPart.DigitsSum();
}

bool IsLucky(size_t firstPart, size_t secondPart)
{
	auto calc_digits_sum = [](size_t number) {
		size_t sum = 0;
		while (number > 0)
		{
			sum += number % 10;
			number = number / 10;
		}
		return sum;
	};

	auto firstSum = calc_digits_sum(firstPart);
	auto secondSum = calc_digits_sum(secondPart);

	return firstPart == secondPart;
}