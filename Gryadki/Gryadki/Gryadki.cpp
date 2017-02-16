#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

char field[1000][1000];

void CheckBed(int i, int j);

int main(int argc, char* argv[])
{
	int bedsCount = 0;
	ifstream input(argv[1]);
	size_t rows;
	size_t colls;
	input >> rows;
	input >> colls;

	// Create border
	for (int j = 0; j != rows + 2; j++)
	{
		field[j][0] = '.';
		field[j][colls + 1] = '.';
	}
	for (int j = 0; j != colls + 2; j++)
	{
		field[0][j] = '.';
		field[rows + 1][j] = '.';
	}

	// Read file
	for (int i = 1; i != rows + 1; i++)
		for (int j = 1; j != colls + 1; j++)
			input >> field[i][j];

	// Process search
	for (int i = 1; i != rows + 1; i++)
		for (int j = 1; j != colls + 1; j++)
		{
			if (field[i][j] == '#')
			{
				bedsCount++;
				CheckBed(i, j);
			}
			else
			{
				field[i][j] = '.';
			}
		}

	// Return fields count
	cout << "On the field " << bedsCount << " beds.\n";

	return 0;
}

void CheckBed(int i, int j)
{
	if (field[i][j] == '#')
	{
		field[i][j] = '.';
		CheckBed(i - 1, j);
		CheckBed(i + 1, j);
		CheckBed(i, j - 1);
		CheckBed(i, j + 1);
	}
}