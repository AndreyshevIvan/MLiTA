#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Exception.h"

namespace
{
	const std::string NULL_RESULTS = "The game has never been played!\n";
}

class CGame
{
public:
	CGame(const std::string &fileName)
	{
		std::ifstream input(fileName);

		if (!input.is_open())
		{
			throw CException("Input can not be opened!\n");
		}

		std::string line;
		getline(input, line);
		std::stringstream stream(line);
		stream >> m_partsCount;
		m_finalsNumbers.resize(m_partsCount);

		for (auto &number : m_finalsNumbers)
		{
			getline(input, line);
			number = std::stoi(line);
		}
	}

	void Start()
	{
		m_isPlayed = true;
	}
	void PrintResults(const std::string &outFileName)
	{
		if (!m_isPlayed)
		{
			throw CException(NULL_RESULTS);
		}

		std::ofstream output(outFileName);
		output << m_results;
	}

private:
	size_t m_partsCount = 0;
	std::vector<size_t> m_finalsNumbers;
	bool m_isPlayed = false;
	std::string m_results;
};