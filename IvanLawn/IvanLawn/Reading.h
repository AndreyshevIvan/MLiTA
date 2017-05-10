#pragma once
#include "Structs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace
{
	const std::string INPUT_FILE = "input.txt";
	const std::string OUTPUT_FILE = "output.txt";

	Rect* ReadRect(std::string &coordsStr);
	Circle* ReadCircle(std::string &coordsStr);

	Rect* ReadRect(std::string &coordsStr)
	{
		std::stringstream stream(coordsStr);

		int x1;
		int y1;
		int x2;
		int y2;

		stream >> x1;
		stream >> y1;
		stream >> x2;
		stream >> y2;

		return new Rect(x1, y1, x2, y2);
	}
	Circle* ReadCircle(std::string &coordsStr)
	{
		std::stringstream stream(coordsStr);

		int x;
		int y;
		size_t radius;

		stream >> x;
		stream >> y;
		stream >> radius;

		return new Circle(x, y, radius);
	}
}

void ReadInput(Rect* rect, Circle* circle);

void ReadInput(Rect* rect, Circle* circle)
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	getline(input, line);
	rect = ReadRect(line);

	getline(input, line);
	circle = ReadCircle(line);
}