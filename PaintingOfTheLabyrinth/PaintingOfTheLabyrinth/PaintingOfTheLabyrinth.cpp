#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::size_t GetMatrixSizeFromFile(std::ifstream& file);
std::vector<std::vector<char>> GetMatrixFromFile(std::ifstream& file);

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	std::ifstream input("INPUT.TXT");
	std::ofstream output("OUTPUT.TXT");

	auto matrixSize = GetMatrixSizeFromFile(input);
	auto matrix = GetMatrixFromFile(input);

	(void)matrix;
	(void)matrixSize;

	return 0;
}

std::size_t GetMatrixSizeFromFile(std::ifstream& file)
{
	(void)file;
	std::size_t size = 0;

	return size;
}

std::vector<std::vector<char>> GetMatrixFromFile(std::ifstream& file)
{
	(void)file;
	std::vector<std::vector<char>> matrix;

	return matrix;
}