#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long Int;

struct Circle
{
	Int x;
	Int y;
	Int radius;
};
struct Rect
{
	Int x1;
	Int y1;
	Int x2;
	Int y2;

	Int LineIntersectsCount(Int lineX, Int lineMinY, Int lineMaxY)
	{
		if (lineX < x1 || lineX > x2 || lineMinY > y2 || lineMaxY < y1)
		{
			return 0;
		}

		return min(lineMaxY, y2) - max(lineMinY, y1) + 1;
	}
};

Int Calculate(Rect rect, Circle circle);
void ReadInput(std::ifstream &input, Rect &rect, Circle &circle);

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	Rect rect;
	Circle circle;
	ReadInput(input, rect, circle);

	Int result = Calculate(rect, circle);
	output << result;

	return 0;
}

Int Calculate(Rect rect, Circle circle)
{
	Int centerMinY = circle.y - circle.radius;
	Int centerMaxY = circle.y + circle.radius;
	Int result = rect.LineIntersectsCount(circle.x, centerMinY, centerMaxY);
	Int currentY = circle.radius;

	for (Int currentX = 1; currentX <= circle.radius; currentX++)
	{
		while (pow(currentX, 2) + pow(currentY, 2) > pow(circle.radius, 2))
		{
			currentY--;
		}

		Int minY = circle.y - currentY;
		Int maxY = circle.y + currentY;
		Int leftX = circle.x - currentX;
		Int rightX = circle.x + currentX;
		Int leftCount = rect.LineIntersectsCount(rightX, minY, maxY);
		Int rightCount = rect.LineIntersectsCount(leftX, minY, maxY);
		result += (leftCount + rightCount);
	}

	return result;
}

void ReadInput(std::ifstream &input, Rect &rect, Circle &circle)
{
	input >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
	input >> circle.x >> circle.y >> circle.radius;
}