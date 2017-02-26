#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

char CORRIDOR_CELL_SYMBOL = '.';
char WALL_CELL_SYMBOL = '#';
char CHECKED_CELL_SYMBOL = 'X';
size_t WALLS_WITHOUT_PAINT = 4;
size_t WALL_AREA_SIZE = 9;

using namespace std;

size_t GetMatrixSizeFromFile(ifstream& file);
vector<vector<char>> GetMatrixFromFile(ifstream& file, size_t matrixSize);
void CreateSourceMatrix(vector<vector<char>>& emptyVector, size_t matrixSize);
void CreateMatrixBorder(vector<vector<char>>& matrix);
void ReadMatrixFromFileToBorderMatrix(ifstream& file, vector<vector<char>>& matrix);

int GetWallsCount(vector<vector<char>> const& matrixForCheck);
void CheckCell(queue<pair<size_t, size_t>>& cells, vector<vector<char>>& matrix, int& wallsCount);

//////////////////////////// DEBUG FUNCTIONS /////////////////////////////
void WriteMatrix(vector<vector<char>> const& matrix);
//////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ifstream input("input.txt");
	ofstream output("output.txt");

	auto matrixSize = GetMatrixSizeFromFile(input);
	auto matrix = GetMatrixFromFile(input, matrixSize);

	auto wallsCount = GetWallsCount(matrix);

	auto paintCount = (wallsCount) * WALL_AREA_SIZE;
	output << paintCount;

	return 0;
}

size_t GetMatrixSizeFromFile(ifstream& file)
{
	size_t size = 0;
	string str;
	getline(file, str);
	stringstream sstring(str);
	sstring >> size;

	return size;
}

vector<vector<char>> GetMatrixFromFile(ifstream& file, size_t matrixSize)
{
	vector<vector<char>> matrix;

	CreateSourceMatrix(matrix, matrixSize);
	CreateMatrixBorder(matrix);
	ReadMatrixFromFileToBorderMatrix(file, matrix);

	return matrix;
}

void CreateSourceMatrix(vector<vector<char>>& matrix, size_t matrixSize)
{
	for (size_t i = 0; i < matrixSize + 2; i++)
	{
		vector<char> newRow;
		matrix.push_back(newRow);
		for (size_t j = 0; j < matrixSize + 2; j++)
		{
			char newCell = CORRIDOR_CELL_SYMBOL;
			matrix[i].push_back(newCell);
		}
	}
}

void CreateMatrixBorder(vector<vector<char>>& matrix)
{
	size_t rows = matrix.size();
	size_t colls = matrix.front().size();

	for (size_t i = 0; i < rows; i++)
	{
		matrix[i][0] = WALL_CELL_SYMBOL;
		matrix[i][colls - 1] = WALL_CELL_SYMBOL;
	}

	for (size_t i = 0; i < colls; i++)
	{
		matrix[0][i] = WALL_CELL_SYMBOL;
		matrix[rows - 1][i] = WALL_CELL_SYMBOL;
	}
}

void ReadMatrixFromFileToBorderMatrix(ifstream& file, vector<vector<char>>& matrix)
{
	auto matrixSize = matrix.size();
	string lineFromFile;

	for (size_t i = 1; i < matrixSize - 1; i++)
	{
		getline(file, lineFromFile);
		stringstream sstring(lineFromFile);
		for (size_t j = 1; j < matrixSize - 1; j++)
		{
			char cellSymbol;
			sstring >> cellSymbol;
			matrix[i][j] = cellSymbol;
		}
	}
}

int GetWallsCount(vector<vector<char>> const& matrixForCheck)
{
	auto matrix = matrixForCheck;
	int wallsCount = 0 - 2;
	queue<pair<size_t, size_t>> cells;
	pair<size_t, size_t> startCellAdress(1, 1);

	cells.push(startCellAdress);

	while (!cells.empty())
	{
		CheckCell(cells, matrix, wallsCount);
	}

	return wallsCount;
}

void CheckCell(queue<pair<size_t, size_t>>& cells, vector<vector<char>>& matrix, int& wallsCount)
{
	auto adress = cells.front();
	cells.pop();
	auto i = adress.first;
	auto j = adress.second;
	auto endAdress = matrix.size() - 2;

	if (matrix[i][j] != CHECKED_CELL_SYMBOL)
	{
		if (i == endAdress && j == endAdress)
		{
			wallsCount -= 2;
		}

		matrix[i][j] = CHECKED_CELL_SYMBOL;

		if (matrix[i][j + 1] == WALL_CELL_SYMBOL) wallsCount++;
		else if (matrix[i][j + 1] == CORRIDOR_CELL_SYMBOL) cells.push(pair<size_t, size_t>(i, j + 1));

		if (matrix[i][j - 1] == WALL_CELL_SYMBOL) wallsCount++;
		else if (matrix[i][j - 1] == CORRIDOR_CELL_SYMBOL) cells.push(pair<size_t, size_t>(i, j - 1));
		
		if (matrix[i + 1][j] == WALL_CELL_SYMBOL) wallsCount++;
		else if (matrix[i + 1][j] == CORRIDOR_CELL_SYMBOL) cells.push(pair<size_t, size_t>(i + 1, j));
		
		if (matrix[i - 1][j] == WALL_CELL_SYMBOL) wallsCount++;
		else if (matrix[i - 1][j] == CORRIDOR_CELL_SYMBOL) cells.push(pair<size_t, size_t>(i - 1, j));
	}
}

// DEBUG FUNCTIONS

void WriteMatrix(vector<vector<char>> const& matrix)
{
	size_t rowsCount = matrix.size();
	size_t collsCount = matrix.front().size();

	for (size_t i = 0; i < rowsCount; i++)
	{
		for (size_t j = 0; j < collsCount; j++)
		{
			cout << matrix[i][j];
		}
		cout << "\n";
	}
}