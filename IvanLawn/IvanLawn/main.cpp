#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

typedef std::pair<int, int> Interval;

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
	}

	Interval GetContainInterval(int yy)
	{
		if (yy == y)
		{
			return std::make_pair(x - radius, x + radius);
		}

		int dRadius = (yy > y) ? (yy - y) : (y - yy);
		int halfContain = (int)sqrt(pow(radius, 2) - pow(dRadius, 2));

		return std::make_pair(x - halfContain, x + halfContain);
	}

	int x;
	int y;
	int radius;
	int minX;
	int maxX;
	int maxY;
	int minY;
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

	int maxY = (rect.y + rect.height > circle.maxY) ? circle.maxY : rect.y + rect.height;
	int minY = (rect.y > circle.minY) ? rect.y : circle.minY;

	int maxX = (rect.x + rect.width < circle.maxX) ? rect.x + rect.width : circle.maxX;
	int minX = (rect.x > circle.minX) ? rect.x : circle.minX;

	for (int y = minY; y <= maxY; y++)
	{
		Interval interval = circle.GetContainInterval(y);

		int newMinX = (minX < interval.first) ? interval.first : minX;
		int newMaxX = (maxX > interval.second) ? interval.second : maxX;

		result += (newMaxX - newMinX + 1);
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