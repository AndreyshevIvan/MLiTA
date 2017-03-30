#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int ARGUMENTS_COUNT = 3;

struct Point
{
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int x = 0;
	int y = 0;
};

void ReadPoints(ifstream& input, vector<Point>& points);
void WritePoints(ofstream& output, const vector<Point> &points);

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		return 1;
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);
	vector<Point> points;

	ReadPoints(input, points);

	int count = 0;

	for (size_t i = 0; i < points.size() - 2; i++)
	{
		int x1 = points[i].x;
		int x2 = points[i + 1].x;
		int x3 = points[i + 2].x;

		int y1 = points[i].y;
		int y2 = points[i + 1].y;
		int y3 = points[i + 2].y;

		int d = (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1);

		if (d < 0)
		{
			count++;
		}
	}

	output << count;

	return 0;
}

void ReadPoints(ifstream& input, vector<Point>& points)
{
	string line = "";
	getline(input, line);
	stringstream sstr(line);
	int size = 0;
	int x = 0;
	int y = 0;
	sstr >> size;

	while (size > 0)
	{
		getline(input, line);
		stringstream stream(line);
		stream >> x;
		stream >> y;
		size--;

		points.push_back(Point(x, y));
	}
}

void WritePoints(ofstream& output, const vector<Point> &points)
{
	(void)output;

	for (auto& point : points)
	{
		cout << point.x << " ";
		cout << point.y << "\n";
	}
}