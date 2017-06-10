#include <vector>
#include <fstream>
#include <iostream>

#include "BigNumber.h"

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second);
CBigNumber CalcBestTicket(const CBigNumber &first, const CBigNumber &second);
CBigNumber GetLargeTicket(const CBigNumber &first, CBigNumber second);
CBigNumber CreateTicket(const CBigNumber &first, const CBigNumber &second);
bool IsLucky(const CBigNumber &first, const CBigNumber &second);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		CBigNumber first;
		CBigNumber second;
		Read(input, first, second);

		auto result = CalcBestTicket(first, second);
		output << result.ToString();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

CBigNumber CalcBestTicket(const CBigNumber &first, const CBigNumber &second)
{
	auto firstSum = first.GetDigitSum();
	auto secondSum = second.GetDigitSum();
	auto ticket = CreateTicket(first, second);

	if (firstSum > secondSum)
	{
		auto bestTicket = GetLargeTicket(first, second);
		return bestTicket - ticket;
	}

	return 0;
}

CBigNumber GetLargeTicket(const CBigNumber &first, CBigNumber second)
{
	int sumDiff = first.GetDigitSum() - second.GetDigitSum();

	for (size_t pos = 0; pos < second.GetLength(); pos++)
	{
		auto digit = second.GetDigit(pos);
		auto allowedToAdd = 9 - digit;
		auto toAdd = (allowedToAdd > sumDiff) ? sumDiff : allowedToAdd;
		
		second.SetDigit(pos, digit + toAdd);
		sumDiff -= toAdd;

		if (sumDiff <= 0) break;
	}

	return CreateTicket(first, second);
}

bool IsLucky(const CBigNumber &first, const CBigNumber &second)
{
	return first.GetDigitSum() == second.GetDigitSum();
}

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second)
{
	std::string N;
	getline(input, N);
	std::string ticketStr;
	getline(input, ticketStr);

	std::string firstStr;
	std::string secondStr;

	for (size_t i = 0; i < (size_t)std::stoi(N); i++)
	{
		firstStr += ticketStr[i];
		secondStr += ticketStr[i + std::stoi(N)];
	}

	first = CBigNumber(firstStr);
	second = CBigNumber(secondStr);
}

CBigNumber CreateTicket(const CBigNumber &first, const CBigNumber &second)
{
	auto firstPart = first.ToString();
	auto secondPart = second.ToString();
	return firstPart + secondPart;
}