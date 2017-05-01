#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include "Exceptions.h"

typedef std::vector<std::string> Text;

class CFileManager
{
public:
	CFileManager(const std::string &inputFile, const std::string &outputFile)
	{
		std::ifstream input(inputFile);
		m_outputFileName = outputFile;

		if (!input.is_open())
		{
			throw CInputException("Input file cannot be opened.");
		}

		std::string fileLine;
		while (getline(input, fileLine))
		{
			m_fileText.push_back(fileLine);
		}
	}

	Text GetAllText()
	{
		return m_fileText;
	}
	void WriteAllText(const Text &text)
	{
		std::ofstream output(m_outputFileName);

		if (!output.is_open())
		{
			throw CInputException("Output file cannot be opened.");
		}

		for (auto line : text)
		{
			output << line << std::endl;
		}
	}

private:
	std::string m_outputFileName;
	Text m_fileText;

};