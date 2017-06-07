#include <iostream>
#include <fstream>
#include <string>
#include "Chess.h"

Field GetGameField(std::ifstream &input);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		auto field = GetGameField(input);
		(void)field;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

Field GetGameField(std::ifstream &input)
{
	size_t height;
	size_t width;
	input >> height >> width;
	
	Field field = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));

	std::string line;
	getline(input, line);

	for (auto &row : field)
	{
		getline(input, line);
		for (size_t i = 0; i < line.size(); i++)
		{
			row[i].SetFigure(line[i]);
		}
	}

	return field;
}