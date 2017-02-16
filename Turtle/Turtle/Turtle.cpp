#include "stdafx.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

const int ARGUMENTS_COUNT = 2;

struct Node
{
	int price = 0;
	pair<int, int> next;
};

void ReadField(ifstream& file, vector<vector<Node>>& field, size_t& sizeX, size_t& sizeY);

void CheckLastRow(vector<vector<Node>>& field, int sizeX, int sizeY);
void CheckLastColl(vector<vector<Node>>& field, int sizeX, int sizeY);
void CheckColls(vector<vector<Node>>& field, int sizeX, int sizeY);

void PrintMatrix(vector<vector<Node>>& field, int sizeX, int sizeY);
void PrintSumAndWay(vector<vector<Node>> const& field, int sizeX, int sizeY);

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		return 0;
	}

	ifstream file(argv[1]);

	size_t sizeX = 0;
	size_t sizeY = 0;
	vector<vector<Node>> field;

	ReadField(file, field, sizeX, sizeY);

	CheckLastRow(field, sizeX, sizeY);
	CheckLastColl(field, sizeX, sizeY);
	CheckColls(field, sizeX, sizeY);

	PrintSumAndWay(field, sizeX, sizeY);

	return 0;
}

void PrintMatrix(vector<vector<Node>>& field, int sizeX, int sizeY)
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			cout << field[y][x].price << "(" << field[y][x].next.first << ", " << field[y][x].next.second << ") ";
		}
		cout << endl;
	}
}

void PrintSumAndWay(vector<vector<Node>> const&field, int sizeX, int sizeY)
{
	cout << field[0][0].price << endl;

	pair<int, int> startPair = pair<int, int>(0, 0);
	while (startPair.first != sizeY - 1 || startPair.second != sizeX - 1)
	{
		cout << "(" << startPair.first + 1 << ", " << startPair.second + 1 << ")" << endl;
		startPair = field[startPair.first][startPair.second].next;
	}

	cout << "(" << sizeY << ", " << sizeX << ")" << endl;
}

void CheckLastRow(vector<vector<Node>>& field, int sizeX, int sizeY)
{
	int x = sizeX - 2;
	int y = sizeY - 1;

	while (x >= 0)
	{
		field[y][x].price = field[y][x].price + field[y][x + 1].price;
		field[y][x].next = pair<int, int>(y, x + 1);
		x--;
	}
}

void CheckLastColl(vector<vector<Node>>& field, int sizeX, int sizeY)
{
	int x = sizeX - 1;
	int y = sizeY - 2;

	while (y >= 0)
	{
		field[y][x].price = field[y][x].price + field[y + 1][x].price;
		field[y][x].next = pair<int, int>(y + 1, x);
		y--;
	}
}

void CheckColls(vector<vector<Node>>& field, int sizeX, int sizeY)
{
	int x = sizeX - 2;
	int y = sizeY - 2;

	while (y >= 0)
	{
		while (x >= 0)
		{
			if (field[y][x].price + field[y][x + 1].price < field[y][x].price + field[y + 1][x].price)
			{
				field[y][x].price += field[y][x + 1].price;
				field[y][x].next = pair<int, int>(y, x + 1);
			}
			else
			{
				field[y][x].price += field[y + 1][x].price;
				field[y][x].next = pair<int, int>(y + 1, x);
			}
			x--;
		}
		x = sizeX - 2;
		y--;
	}
}

void ReadField(ifstream& file, vector<vector<Node>>& field, size_t& sizeX, size_t& sizeY)
{
	file >> sizeY;
	file >> sizeX;

	for (size_t i = 0; i < sizeY; i++)
	{
		auto vec = new vector<Node>();
		field.push_back(*vec);
		for (size_t j = 0; j < sizeX; j++)
		{
			int tmpPrice = 0;
			auto node = new Node();
			field[i].push_back(*node);
			file >> tmpPrice;
			field[i][j].price = tmpPrice;
			field[i][j].next = pair<int, int>(i, j);
		}
	}
}