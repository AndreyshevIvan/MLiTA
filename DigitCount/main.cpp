#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>

typedef unsigned long long Int;

namespace
{
	const Int MAX_VALUE =  Int(-1);
}

Int Calculate(Int first, Int second);
std::vector<Int> GetCategoryVector(Int number);
Int CalcDigitsCount(const std::vector<Int> &categoryVect);
Int StringTest(Int first, Int second);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		Int first;
		Int second;

		input >> first >> second;
		//output << StringTest(first, second) << '\n';
		output << Calculate(first, second);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		return 1;
	}

	return 0;
}

Int Calculate(Int first, Int second)
{
	size_t firstDigitsCount = std::to_string(first).size();

	if (first == second)
	{
		return Int(firstDigitsCount);
	}

	auto firstCategoryVect = GetCategoryVector(first);
	auto secondCategoryVect = GetCategoryVector(second);

	auto firstNumberDigitsCount = CalcDigitsCount(firstCategoryVect);
	auto secondNumberDigitsCount = CalcDigitsCount(secondCategoryVect);

	return secondNumberDigitsCount - firstNumberDigitsCount + firstDigitsCount;
}

std::vector<Int> GetCategoryVector(Int number)
{
	if (number == 0)
	{
		return std::vector<Int>(1, 0);
	}

	size_t category = std::to_string(number).size();
	std::vector<Int> result(category, 9);

	for (size_t i = 1; i < category - 1; i++)
	{
		result[i] = 9 * Int(pow(10, i));
	}

	result.back() = number - Int(pow(10, category - 1)) + 1;

	return result;
}

Int CalcDigitsCount(const std::vector<Int> &categoryVect)
{
	Int result = 0;
	size_t digitsCount = 1;

	for (auto &digitsInCategory : categoryVect)
	{
		if (MAX_VALUE - digitsInCategory * digitsCount < result)
		{
			throw std::overflow_error("Digits count overflow.");
		}

		result += digitsInCategory * digitsCount;
		digitsCount++;
	}

	return result;
}

Int StringTest(Int first, Int second)
{
	std::string str;
	for (first; first <= second; first++)
	{
		str += std::to_string(first);
	}

	return str.size();
}