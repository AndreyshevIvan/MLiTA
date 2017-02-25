#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

char CORRIDOR_CELL_SYMBOL = '.';
char WALL_CELL_SYMBOL = '#';

using namespace std;

size_t GetMatrixSizeFromFile(ifstream& file);
vector<vector<char>> GetMatrixFromFile(ifstream& file, size_t matrixSize);
void CreateSourceMatrix(vector<vector<char>>& emptyVector, size_t matrixSize);
void CreateMatrixBorder(vector<vector<char>>& matrix);
void ReadMatrixFromFileToBorderMatrix(ifstream& file, vector<vector<char>>& matrix);

// DEBUG FUNCTIONS
void WriteMatrix(vector<vector<char>> const& matrix);

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ifstream input("INPUT.TXT");
	ofstream output("OUTPUT.TXT");

	auto matrixSize = GetMatrixSizeFromFile(input);
	auto matrix = GetMatrixFromFile(input, matrixSize);

	(void)matrix;

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
	(void)file;
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