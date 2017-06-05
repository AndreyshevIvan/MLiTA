#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>

std::vector<int> ReadInput();
void WriteSum(int result);
void WriteUpdate(size_t from, size_t to, int delta);
void WriteError(const std::string &message = "");

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

void WriteSum(int result)
{
	std::cout << "Sum result = " << result << std::endl;
}

void WriteUpdate(size_t from, size_t to, int delta)
{
	std::cout << "Update elements from " << from << " to " << to << " on " << delta << std::endl;
}

void WriteError(const std::string &message)
{
	std::cout << "Invalid command." << std::endl << message << std::endl;
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