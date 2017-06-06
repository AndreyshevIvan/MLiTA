#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include "SegmentTree.h"

namespace
{
	const std::string INPUT_FILE = "input.txt";
	const std::string OUTPUT_FILE = "output.txt";
}

void EnterProcess(std::ifstream &input, IPowerLine &powerLine);
void ReadInput(std::ifstream &input, int &columnCount, int &commandsCount);

int main()
{
	try
	{
		std::ifstream input(INPUT_FILE);

		int columnCount;
		int commandsCount;

		ReadInput(input, columnCount, commandsCount);
		CSegementTree powerLine(columnCount - 1);
		EnterProcess(input, powerLine);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void EnterProcess(std::ifstream &input, IPowerLine &powerLine)
{
	std::ofstream output(OUTPUT_FILE);
	std::string command;
	int cmdType;

	while (getline(input, command))
	{
		std::stringstream stream = std::stringstream(command);
		size_t leftColumn;
		size_t rightColumn;
		stream >> cmdType >> leftColumn >> rightColumn;

		if (cmdType == ADD_SNOW)
		{
			int snowCount;
			stream >> snowCount;
			powerLine.AddSnow(leftColumn, rightColumn, snowCount);
		}
		else if (cmdType == GET_SNOW_COUNT)
		{
			output << powerLine.GetSnowSum(leftColumn, rightColumn) << std::endl;
		}
	}
}

void ReadInput(std::ifstream &input, int &columnCount, int &commandsCount)
{
	std::string inputLine;
	getline(input, inputLine);
	std::stringstream stream(inputLine);
	stream >> columnCount >> commandsCount;
}