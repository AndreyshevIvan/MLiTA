#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Structs.h"
#include "Reading.h"

size_t Calculate(Rect rect, Circle circle);

int main()
{
	Rect rect;
	Circle circle;

	ReadInput(rect, circle);

	size_t result = Calculate(rect, circle);
	PrintResult(result);

	return 0;
}

size_t Calculate(Rect rect, Circle circle)
{
	size_t result = 0;

	int maxY = (rect.y > circle.maxY) ? circle.maxY : rect.y;
	int minY = (rect.y - rect.height > circle.minY) ? rect.y - rect.height : circle.minY;

	int maxX = (rect.x + rect.width < circle.maxX) ? rect.x + rect.width : circle.maxX;
	int minX = (rect.x > circle.minX) ? rect.x : circle.minX;

	for (int y = maxY; y >= minY; y--)
	{
		auto interval = circle.GetXPointsFromLine(y);

		int newMinX = (minX < interval.first) ? interval.first : minX;
		int newMaxX = (maxX > interval.second) ? interval.second : maxX;

		result += (newMaxX - newMinX + 1);
	}

	return result;
}