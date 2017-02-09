#include "stdafx.h"

#include <iostream>
#include <fstream>

using namespace std;

char field[1000][1000];
int bedCount = 0;

void CheckBed(int i, int j)
{
	if (field[i][j] == '#')
	{
		field[i][j] = 'A';
		CheckBed(i - 1, j);
		CheckBed(i + 1, j);
		CheckBed(i, j - 1);
		CheckBed(i, j + 1);
	}
}

int main(int argc, char* argv[])
{
	ifstream input(argv[1]);
	ofstream output("output.txt");

	size_t rows;
	size_t colls;

	input >> rows;
	input >> colls;

	for (int j = 0; j != rows + 2; j++)
	{
		field[j][0] = 'A';
		field[j][colls + 1] = 'A';
	}

	for (int j = 0; j != colls + 2; j++)
	{
		field[0][j] = 'A';
		field[rows + 1][j] = 'A';
	}

	for (int i = 1; i != rows + 1; i++)
		for (int j = 1; j != colls + 1; j++)
			input >> field[i][j];


	for (int i = 1; i != rows + 1; i++)
		for (int j = 1; j != colls + 1; j++)
		{
			if (field[i][j] == '#')
			{
				bedCount++;
			}
			CheckBed(i, j);
		}


	for (int i = 0; i != rows + 2; i++)
	{
		for (int j = 0; j != colls + 2; j++)
		{
			output << field[i][j];
		}
		output << "\n";
	}

	output << bedCount;




	return 0;
}