#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

typedef std::pair<double, double> Interval;

struct Circle
{
	Circle(int x, int y, size_t radius)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->minX = x - radius;
		this->maxX = x + radius;
		this->maxY = y + radius;
		this->minY = y - radius;
		sqrR = radius * radius;
	}

	Interval GetPointsOnLine(int XX)
	{/*
		double dXX = (XX < x) ? (x - XX) : (XX - x);
		double halfLine = sqrt(sqrR - pow(dXX, 2));

		return std::make_pair(y - halfLine, y + halfLine);
		*/
		
		double C = y * y - sqrR + (XX - x) * (XX - x);
		double D = (y * y) - C;

		double y1 = y - sqrt(D);
		double y2 = y + sqrt(D);

		return std::make_pair(y1, y2);
		
	}

	int x;
	int y;
	int radius;
	int minX;
	int maxX;
	int maxY;
	int minY;
	int sqrR;
};
struct Rect
{
	Rect(int x1, int y1, int x2, int y2)
	{
		x = x1;
		y = y1;
		width = x2 - x1;
		height = y2 - y1;
	}

	int x;
	int y;
	int width = 0;
	int height = 0;
};

size_t Calculate(Rect rect, Circle circle);
Rect ReadRect(std::ifstream &input);
Circle ReadCircle(std::ifstream &input);
void PrintResult(size_t result, const std::string &fileName);
int min(int a, int b);
int max(int a, int b);

int main()
{
	std::ifstream input("input.txt");
	Rect rect = ReadRect(input);
	Circle circle = ReadCircle(input);

	size_t result = Calculate(rect, circle);
	PrintResult(result, "output.txt");

	return 0;
}

size_t Calculate(Rect rect, Circle circle)
{
	size_t result = 0;

	int maxY = min(rect.y + rect.height, circle.maxY);
	int minY = max(rect.y, circle.minY);

	int maxX = min(rect.x + rect.width, circle.maxX);
	int minX = max(rect.x, circle.minX);

	for (int x = minX; x <= maxX; x++)
	{
		Interval interval = circle.GetPointsOnLine(x);

		int newMaxY = min(maxY, interval.second);
		int newMinY = max(minY, interval.first);

		result += (newMaxY - newMinY + 1);
	}

	return result;
}

Rect ReadRect(std::ifstream &input)
{
	std::string line;
	getline(input, line);
	std::stringstream stream(line);

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
Circle ReadCircle(std::ifstream &input)
{
	std::string line;
	getline(input, line);
	std::stringstream stream(line);

	int x;
	int y;
	size_t radius;

	stream >> x;
	stream >> y;
	stream >> radius;

	return Circle(x, y, radius);
}
void PrintResult(size_t result, const std::string &fileName)
{
	std::ofstream output(fileName);
	output << result << std::endl;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}