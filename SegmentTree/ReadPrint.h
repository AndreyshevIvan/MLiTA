#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>

std::vector<int> ReadInput();
void WriteSum(long long result);
void WriteUpdate(size_t from, size_t to, int delta);
void WriteArray(const std::vector<int> &arr);

std::vector<int> ReadInput()
{
	std::vector<int> result;
	std::ifstream file("input.txt");
	std::string nullLine;
	getline(file, nullLine);

	int number;
	while (file >> number)
	{
		result.push_back(number);
	}

	return result;
}

void WriteSum(long long result)
{
	std::cout << "Sum result = " << result << std::endl;
}

void WriteUpdate(size_t from, size_t to, int delta)
{
	std::cout << "Update elements from " << from
		<< " to " << to
		<< " on " << delta << std::endl;
}

void WriteArray(const std::vector<int> &arr)
{
	std::cout << "Array: ";
	for (auto element : arr)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}