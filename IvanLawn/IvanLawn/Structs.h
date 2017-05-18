#pragma once

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
		this->maxY = y + radius;
		this->minY = y - radius;
	}

	std::pair<int, int> GetXPointsFromLine(int yy)
	{
		int minusC = radius * radius - (yy - y) * (yy - y) - x * x;
		int disc = 4 * x * x + 4 * minusC;

		int x1 = (x - (int)(sqrt(disc) + 0.5) / 2);
		int x2 = (x + (int)(sqrt(disc) + 0.5) / 2);

		return std::make_pair(x1, x2);
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
	Rect()
	{
	}
	Rect(int x1, int y1, int x2, int y2)
	{
		x = (x1 < x2) ? x1 : x2;
		y = (y1 > y2) ? y1 : y2;

		width = (x1 > x2) ? x1 - x2 : x2 - x1;
		height = (y1 > y2) ? y1 - y2 : y2 - y1;

		width = std::abs(width);
		height = std::abs(height);
	}

	int x; // top left x
	int y; // top left y
	int width = 0;
	int height = 0;
};