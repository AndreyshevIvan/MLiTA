#pragma once
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>

typedef std::vector<std::vector<size_t>> Helix;

enum struct Direction
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
};

class CHelix
{
public:
	CHelix(int size)
	{
		if (size < 0)
		{
			throw std::invalid_argument("CHelix.Constructor: Helix size can not be less than 0.");
		}

		m_helix = Helix(size, std::vector<size_t>(size, 1));
		size_t row = 0;
		size_t coll = 0;
		size_t number = 1;

		while (size >= 1)
		{
			InitLine(row, coll, size, number, Direction::RIGHT);
			number += size - 1;
			InitLine(row, coll + size - 1, size, number, Direction::DOWN);
			number += size - 1;
			InitLine(row + size - 1, coll + size - 1, size, number, Direction::LEFT);
			number += size - 1;
			InitLine(row + size - 1, coll, size - 1, number, Direction::UP);
			number += size - 1;

			row++;
			coll++;
			size -= 2;
		}
	}

	void Print(std::ofstream &output)
	{
		for (auto helixRow : m_helix)
		{
			for (size_t i = 0; i < helixRow.size(); i++)
			{
				output << helixRow[i];
				if (i != helixRow.size() - 1)
				{
					output << ' ';
				}
			}
			output << std::endl;
		}
	}

private:
	CHelix() {};

	void InitLine(size_t row, size_t coll, size_t size, size_t number, Direction dir)
	{
		while (size != 0)
		{
			m_helix[row][coll] = number;
			IncByDir(dir, row, coll);
			number++;
			size--;
		}
	}
	void IncByDir(Direction dir, size_t &row, size_t &coll)
	{
		switch (dir)
		{
		case Direction::RIGHT:
			coll++;
			break;
		case Direction::DOWN:
			row++;
			break;
		case Direction::LEFT:
			coll--;
			break;
		case Direction::UP:
			row--;
			break;
		default:
			break;
		}
	}

	Helix m_helix;
};