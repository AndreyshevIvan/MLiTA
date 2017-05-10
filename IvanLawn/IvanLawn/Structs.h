#pragma once
#include <string>

struct Circle
{
	Circle(int x, int y, size_t radius)
	{
		(void)x;
		(void)y;
		(void)radius;
	}

	int x;
	int y;
	int radius;
};

struct Rect
{
	Rect(int x1, int y1, int x2, int y2)
	{
		(void)x1;
		(void)y1;
		(void)x2;
		(void)y2;
	}

	int x1;
	int y1;
	int x2;
	int y2;
	int width = 0;
	int height = 0;
};
