#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Circle
{
	int x;
	int y;
	int radius;
};
struct Rect
{
	int x1;
	int y1;
	int x2;
	int y2;

	size_t LineIntersectsCount(int lineX, int lineMinY, int lineMaxY)
	{
		if (lineX < x1 || lineX > x2 || lineMinY > y2 || lineMaxY < y1)
		{
			return 0;
		}

		return size_t(min(lineMaxY, y2) - max(lineMinY, y1) + 1);
	}
};

size_t Calculate(Rect rect, Circle circle);
void ReadInput(std::ifstream &input, Rect &rect, Circle &circle);

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	Rect rect;
	Circle circle;
	ReadInput(input, rect, circle);

	size_t result = Calculate(rect, circle);
	output << result;

	return 0;
}

size_t Calculate(Rect rect, Circle circle)
{
	int centerMinY = circle.y - circle.radius;
	int centerMaxY = circle.y + circle.radius;
	size_t result = rect.LineIntersectsCount(circle.x, centerMinY, centerMaxY);
	int currentY = circle.radius;

	for (int currentX = 1; currentX <= circle.radius; currentX++)
	{
		while (pow(currentX, 2) + pow(currentY, 2) > pow(circle.radius, 2))
		{
			currentY--;
		}

		int minY = circle.y - currentY;
		int maxY = circle.y + currentY;
		int leftX = circle.x - currentX;
		int rightX = circle.x + currentX;
		size_t leftCount = rect.LineIntersectsCount(rightX, minY, maxY);
		size_t rightCount = rect.LineIntersectsCount(leftX, minY, maxY);
		result += (leftCount + rightCount);
	}

	return result;
}

void ReadInput(std::ifstream &input, Rect &rect, Circle &circle)
{
	input >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
	input >> circle.x >> circle.y >> circle.radius;
}