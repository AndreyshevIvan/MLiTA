#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace
{
	const std::string INPUT_FILE = "input.txt";
	const std::pair<size_t, size_t> WIN_CELL = std::make_pair(1, 1);
}

typedef std::pair<size_t, size_t> Coordinate;
typedef std::vector<Coordinate> Coordinates;
typedef std::vector<bool> GameResults;

Coordinates ReadCoordinates(std::ifstream &input);
GameResults GetResults(const Coordinates &startCoordinates);
size_t GetStepsCount(const Coordinate &position);
bool ProcessGameLoop(Coordinate startPosition);
void PrintRsults(const GameResults &gameResults);

int main()
{
	std::ifstream input(INPUT_FILE);

	auto coordinates = ReadCoordinates(input);
	auto results = GetResults(coordinates);
	PrintRsults(results);

	return 0;
}

Coordinates ReadCoordinates(std::ifstream &input)
{
	Coordinates result;
	std::string fileLine;
	getline(input, fileLine);
	std::stringstream stream(fileLine);
	int coordinatesCount;
	stream >> coordinatesCount;

	while (coordinatesCount > 0)
	{
		coordinatesCount--;
		getline(input, fileLine);
		std::stringstream coordinateStream(fileLine);
		size_t x;
		size_t y;
		coordinateStream >> x;
		coordinateStream >> y;
		result.push_back(std::make_pair(x, y));
	}

	return result;
}

GameResults GetResults(const Coordinates &startCoordinates)
{
	GameResults result;

	for (auto coordinate : startCoordinates)
	{
		auto isFirstWin = ProcessGameLoop(coordinate);
		result.push_back(isFirstWin);
	}

	return result;
}

size_t GetStepsCount(const Coordinate &position)
{
	size_t largestCoord = position.first;

	if (largestCoord < position.second)
	{
		largestCoord = position.second;
	}

	return largestCoord + 1;
}

bool ProcessGameLoop(Coordinate startPosition)
{
	bool isFirstTurn = true;

	while (startPosition != WIN_CELL)
	{
		if (startPosition.first != WIN_CELL.first)
		{
			startPosition.first--;
		}
		if (startPosition.second != WIN_CELL.second)
		{
			startPosition.second--;
		}
		if (startPosition != WIN_CELL)
		{
			isFirstTurn = !isFirstTurn;
		}
	}

	return isFirstTurn;
}

void PrintRsults(const GameResults &gameResults)
{
	for (auto result : gameResults)
	{
		char winPlayer = (result) ? '1' : '2';
		std::cout << winPlayer << std::endl;
	}
}