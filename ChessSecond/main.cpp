#include <iostream>
#include <fstream>
#include <string>
#include "Chess.h"

Chess GetGame(std::ifstream &input);

void MarkFireByRooks(Chess &game);
void MarkFireByKnights(Chess &game);
void MarkFireByBishops(Chess &game);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		Chess game = GetGame(input);

		MarkFireByRooks(game);
		MarkFireByKnights(game);
		MarkFireByBishops(game);

		output << game.onFireCount << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

void MarkFireByRooks(Chess &game)
{
	for (Coordinate figureCoord : game.rookCoords)
	{
		Coordinate tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.second--;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));

		tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.second++;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));

		tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.first--;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));

		tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.first++;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));
	}
}
void MarkFireByKnights(Chess &game)
{
	auto getKnightWays = [=](const Coordinate &knightCoord) {
		auto h = knightCoord.first;
		auto v = knightCoord.second;
		std::vector<Coordinate> result;
		result.push_back(std::make_pair(h - 2, v - 1));
		result.push_back(std::make_pair(h - 2, v + 1));
		result.push_back(std::make_pair(h + 2, v - 1));
		result.push_back(std::make_pair(h + 2, v + 1));
		result.push_back(std::make_pair(h - 1, v - 2));
		result.push_back(std::make_pair(h + 1, v - 2));
		result.push_back(std::make_pair(h - 1, v + 2));
		result.push_back(std::make_pair(h + 1, v + 2));
		return result;
	};

	for (Coordinate figureCoord : game.knightCoords)
	{
		for (auto knightCoord : getKnightWays(figureCoord))
		{
			if (!game.IsCoordValid(knightCoord))
			{
				continue;
			}

			game.SetFire(knightCoord);
		}
	}
}
void MarkFireByBishops(Chess &game)
{
	for (Coordinate figureCoord : game.bishopCoords)
	{
		Coordinate tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.first--;
			tmpCoord.second--;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));

		tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.first++;
			tmpCoord.second++;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));

		tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.first--;
			tmpCoord.second++;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));

		tmpCoord = figureCoord;
		do
		{
			game.SetFire(tmpCoord);
			tmpCoord.first++;
			tmpCoord.second--;
		} while (game.IsCoordValid(tmpCoord) && game.IsEmpty(tmpCoord));
	}
}

Chess GetGame(std::ifstream &input)
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

	return Chess(field);
}