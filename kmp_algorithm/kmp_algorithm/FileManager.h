#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "Exceptions.h"

class CFileManager
{
public:
	static std::vector<std::string> GetAllText(const std::string &readFileName)
	{
		std::ifstream input(readFileName);

		if (!input.is_open())
		{
			throw CInputException("Input file cannot be opened.");
		}

		std::string fileLine;
		std::vector<std::string> fileText;

		while (getline(input, fileLine))
		{
			fileText.push_back(fileLine);
		}

		return fileText;
	}
	static void WriteAllText(const std::string &outFileName, const std::vector<std::string> &text)
	{
		std::ofstream output(outFileName);

		if (!output.is_open())
		{
			throw CInputException("Output file cannot be opened.");
		}

		for (auto line : text)
		{
			output << line << std::endl;
		}
	}
	static void WriteAllText(const std::string &outFileName, const std::string &line)
	{
		auto text = { line };
		WriteAllText(outFileName, text);
	}
};