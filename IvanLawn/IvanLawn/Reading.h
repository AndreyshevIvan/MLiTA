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

	Rect ReadRect(std::string &coordsStr);
	Circle ReadCircle(std::string &coordsStr);

	Rect ReadRect(std::string &coordsStr)
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

		return Rect(x1, y1, x2, y2);
	}
	Circle ReadCircle(std::string &coordsStr)
	{
		std::stringstream stream(coordsStr);

		int x;
		int y;
		size_t radius;

		stream >> x;
		stream >> y;
		stream >> radius;

		return Circle(x, y, radius);
	}
}

void ReadInput(Rect &rect, Circle &circle);
void PrintResult(size_t result);
void Write(const Rect &rect);
void Write(const Circle &circle);

void ReadInput(Rect &rect, Circle &circle)
{
	std::ifstream input(INPUT_FILE);
	std::string line;

	getline(input, line);
	rect = ReadRect(line);

	getline(input, line);
	circle = ReadCircle(line);
}
void PrintResult(size_t result)
{
	std::ofstream output(OUTPUT_FILE);
	output << result << std::endl;
}
void Write(const Rect &rect)
{
	std::cout << "Rectangle:\n"
		<< "X: " << rect.x << std::endl
		<< "Y: " << rect.y << std::endl
		<< "Width: " << rect.width << std::endl
		<< "Height: " << rect.height << std::endl;
}
void Write(const Circle &circle)
{
	std::cout << "Circle:\n"
		<< "X: " << circle.x << std::endl
		<< "Y: " << circle.y << std::endl
		<< "Radius: " << circle.radius << std::endl;
}