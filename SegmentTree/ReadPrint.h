#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>

std::vector<int> ReadInput();
void WriteRsq(int rsqResult);
void WriteUpdate(int position, int delta);
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

void WriteRsq(int rsqResult)
{
	std::cout << "Rsq result = " << rsqResult << std::endl;
}

void WriteUpdate(int position, int delta)
{
	std::cout << "Increment element " << position << " on " << delta << std::endl;
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