#pragma once
#include <vector>

namespace
{
	const char ROOK_SYMBOL = 'R';
	const char KNIGHT_SYMBOL = 'K';
	const char BISHOP_SYMBOL = 'B';
}

enum Figure
{
	EMPTY,
	ROOK,
	KNIGHT,
	BISHOP,
};

struct Cell
{
	bool isOnFire = false;
	Figure figure = EMPTY;

	void SetFigure(char symbol)
	{
		if (symbol == ROOK_SYMBOL) figure = ROOK;
		if (symbol == KNIGHT_SYMBOL) figure = KNIGHT;
		if (symbol == BISHOP_SYMBOL) figure = BISHOP;
	}
	bool SetFire()
	{
		if (isOnFire) return false;
		isOnFire = (figure == EMPTY);
		return isOnFire;
	}
};

typedef std::vector<std::vector<Cell>> Field;
typedef std::pair<int, int> Coordinate;
typedef std::vector<Coordinate> Coords;

struct Chess
{
	Chess(const Field &field)
	{
		this->field = field;
		height = this->field.size();
		width = this->field.front().size();

		for (size_t i = 0; i < this->field.size(); i++)
		{
			for (size_t j = 0; j < this->field[i].size(); j++)
			{
				Figure figure = this->field[i][j].figure;
				Coordinate coordinate = std::make_pair(i, j);
				if (figure == ROOK) rookCoords.push_back(coordinate);
				if (figure == KNIGHT) knightCoords.push_back(coordinate);
				if (figure == BISHOP) bishopCoords.push_back(coordinate);
			}
		}
	}

	bool IsCoordValid(const Coordinate &coord)
	{
		if (coord.first < 0) return false;
		if (coord.first > (int)height - 1) return false;
		if (coord.second < 0) return false;
		if (coord.second >(int)width - 1) return false;
		return true;
	}
	bool IsEmpty(const Coordinate &coordinate)
	{
		return field[coordinate.first][coordinate.second].figure == EMPTY;
	}
	void SetFire(const Coordinate &coordinate)
	{
		if (field[coordinate.first][coordinate.second].SetFire())
		{
			onFireCount++;
		}
	}

	Field field;
	size_t width;
	size_t height;
	size_t onFireCount = 0;

	Coords rookCoords;
	Coords knightCoords;
	Coords bishopCoords;
};
