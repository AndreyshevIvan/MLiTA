#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>

std::vector<int> ReadInput();
void WriteRsq(int rsqResult);
void WriteUpdate(int position);

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
	std::cout << "Inc " << position << " element on " << delta << std::endl;
}