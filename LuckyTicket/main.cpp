#include <fstream>
#include <iostream>

#include "BigNumber.h"

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second);
CBigNumber CalcTicketsForLuck(const CBigNumber &first, const CBigNumber &second);
CBigNumber GetLargeFirstPart(const CBigNumber &first, CBigNumber second);
CBigNumber GetFirstPartTicket(const CBigNumber &first, const CBigNumber &second);
CBigNumber CreateTicket(const CBigNumber &first, const CBigNumber &second);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		CBigNumber first;
		CBigNumber second;
		Read(input, first, second);

		auto result = CalcTicketsForLuck(first, second);
		output << result.ToString() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

CBigNumber CalcTicketsForLuck(const CBigNumber &first, const CBigNumber &second)
{
	auto firstSum = first.GetDigitSum();
	auto secondSum = second.GetDigitSum();
	auto ticket = CreateTicket(first, second);

	if (firstSum == secondSum)
	{
		return CBigNumber(0);
	}

	if (firstSum > secondSum)
	{
		auto bestTicket = GetLargeFirstPart(first, second);
		return bestTicket - ticket;
	}

	auto firstPartTicket = GetFirstPartTicket(first, second);
	auto ticketParts = firstPartTicket.Split();
	auto bestTicket = GetLargeFirstPart(ticketParts.first, ticketParts.second);

	return bestTicket - ticket;
}

CBigNumber GetLargeFirstPart(const CBigNumber &first, CBigNumber second)
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

CBigNumber GetFirstPartTicket(const CBigNumber &first, const CBigNumber &second)
{
	auto ticket = CreateTicket(first, second);

	for (size_t pos = 0; pos < first.GetLength(); pos++)
	{
		ticket.SetDigit(pos, 0);
		ticket.SmartIncrement(pos + 1);

		auto ticketParts = ticket.Split();
		auto firstSum = ticketParts.first.GetDigitSum();
		auto secondSum = ticketParts.second.GetDigitSum();
		if (firstSum >= secondSum) break;
	}

	return ticket;
}

void Read(std::ifstream &input, CBigNumber &first, CBigNumber &second)
{
	size_t N;
	input >> N;
	std::string ticketStr;
	getline(input, ticketStr);
	input >> ticketStr;
	CBigNumber ticket(ticketStr);

	first = ticket.Split().first;
	second = ticket.Split().second;
}

CBigNumber CreateTicket(const CBigNumber &first, const CBigNumber &second)
{
	auto firstPart = first.ToString();
	auto secondPart = second.ToString();
	return firstPart + secondPart;
}