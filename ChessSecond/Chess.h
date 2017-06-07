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
		switch (symbol)
		{
		case ROOK_SYMBOL:
			figure = ROOK;
			break;
		case KNIGHT_SYMBOL:
			figure = KNIGHT;
			break;
		case BISHOP_SYMBOL:
			figure = BISHOP;
			break;
		default:
			break;
		}
	}
	bool IsCanFire()
	{
		return figure == EMPTY;
	}
};

typedef std::vector<std::vector<Cell>> Field;