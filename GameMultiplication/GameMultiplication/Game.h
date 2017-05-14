#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <exception>

namespace
{
	const std::vector<size_t> GAME_MULTIPLIERS = { 2, 3, 4, 5 };
}

class CGame
{
public:
	CGame(const std::string &fileName)
	{
		std::ifstream input(fileName);

		if (!input.is_open())
		{
			throw std::exception("Input can not be opened!\n");
		}

		std::string line;
		getline(input, line);
		std::stringstream stream(line);
		stream >> m_partsCount;
		m_winNumbers.resize(m_partsCount);

		for (auto &number : m_winNumbers)
		{
			getline(input, line);
			number = std::stoi(line);
		}
	}

	void Start()
	{
		m_isPlayed = true;

		for (auto winNumber : m_winNumbers)
		{
			m_moveVariants.clear();
			auto isFirstWin = IsFirstWin(1, winNumber);
			AddResult(isFirstWin);
		}
	}
	void PrintResults(const std::string &outFileName)
	{
		if (!m_isPlayed)
		{
			throw std::exception("The game has never been played!\n");
		}

		std::ofstream output(outFileName);
		output << m_results;
	}

private:
	bool IsFirstWin(size_t startNumber, size_t winNumber)
	{
		auto move = m_moveVariants.find(startNumber);
		if (move != m_moveVariants.end())
		{
			return move->second;
		}

		for (auto multiplier : GAME_MULTIPLIERS)
		{
			size_t newStart = startNumber * multiplier;

			if (newStart >= winNumber || !IsFirstWin(newStart, winNumber))
			{
				m_moveVariants.insert(std::make_pair(startNumber, true));
				return true;
			}
		}

		return false;
	}

	void AddResult(bool isFirstWin)
	{
		auto result = (isFirstWin) ? "1\n" : "2\n";
		m_results += result;
	}

	bool m_isPlayed = false;
	size_t m_partsCount = 0;
	std::string m_results;
	std::vector<size_t> m_winNumbers;
	std::map<size_t, bool> m_moveVariants;
};