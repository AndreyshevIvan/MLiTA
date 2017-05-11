#pragma once
#include <string>
#include <cmath>

struct Circle
{
	Circle()
	{
	}
	Circle(int x, int y, size_t radius)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->minX = x - radius;
		this->maxX = x + radius;
	}

	bool Contain(int xx, int yy)
	{
		auto distance = pow(xx - x, 2) + pow(yy - y, 2);
		return sqrt(distance) <= radius;
	}

	int x;
	int y;
	int radius;
	int minX;
	int maxX;
};

struct Rect
{
	Rect()
	{
	}
	Rect(int x1, int y1, int x2, int y2)
	{
		x = (x1 < x2) ? x1 : x2;
		y = (y1 > y2) ? y1 : y2;

		width = (x1 > x2) ? x1 - x2 : x2 - x1;
		height = (y1 > y2) ? y1 - y2 : y2 - y1;

		width = abs(width);
		height = abs(height);
	}

	int x; // top left x
	int y; // top left y
	int width = 0;
	int height = 0;
};
