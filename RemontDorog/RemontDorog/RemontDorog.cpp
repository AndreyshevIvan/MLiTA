#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Point
{
	Point(int position, bool isPointStart)
		:pos(position)
		,isStart(isPointStart)
	{

	}

	int pos;
	bool isStart;
};

int GetIntervalsCount(ifstream& input);
int GetExpertsCount(ifstream& input);

void ReadIntervals(ifstream& input, vector<pair<int, int>>& intervals);
void ConvertToPoints(vector<Point>& points, vector<pair<int, int>> const& intervalsPair);
void SortIntervals(vector<Point>& points);
void CalculateIntervals(vector<Point> const& points, int experts);

// DEBUG
void WriteVectorOfIntervals(vector<Point>& points);

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ifstream input(argv[1]);

	int intervalsCount = GetIntervalsCount(input);
	int expertsCount = GetExpertsCount(input);

	(void)intervalsCount;
	(void)expertsCount;

	vector<pair<int, int>> intervalsPair;
	vector<Point> points;

	ReadIntervals(input, intervalsPair);
	ConvertToPoints(points, intervalsPair);
	WriteVectorOfIntervals(points);

	SortIntervals(points);
	WriteVectorOfIntervals(points);

	CalculateIntervals(points, expertsCount);

	return 0;
}


bool LessThen(Point elem1, Point elem2)
{
	return elem1.pos < elem2.pos;
}
void SortIntervals(vector<Point>& points)
{
	sort(points.begin(), points.end(), LessThen);
}

void ConvertToPoints(vector<Point>& points, vector<pair<int, int>> const& intervalsPair)
{
	for (auto interval : intervalsPair)
	{
		Point startPoint = Point(interval.first, true);
		points.push_back(startPoint);
		Point endPoint = Point(interval.second, false);
		points.push_back(endPoint);
	}
}

void CalculateIntervals(vector<Point> const& points, int experts)
{
	int currCount = 0;
	int newStart = -1;

	int result = 0;
	int currPos = 0;

	for (auto point : points)
	{
		currPos = point.pos;

		if (!point.isStart)
		{
			if (currCount == experts)
			{
				newStart = currPos;
			}
			currCount--;
		}

		if (point.isStart)
		{
			currCount++;

			if (currCount == experts)
			{
				newStart = currPos;
			}

		}
	}

	cout << result;

}

int GetIntervalsCount(ifstream& input)
{
	int result = 0;

	input >> result;

	return result;
}

int GetExpertsCount(ifstream& input)
{
	int result = 0;

	input >> result;

	return result;
}

void ReadIntervals(ifstream& input, vector<pair<int, int>>& intervals)
{
	string line;
	int start;
	int end;

	getline(input, line);

	while (getline(input, line))
	{
		cout << "New pair: ";
		cout << line << "\n";
		stringstream sstr(line);

		sstr >> start;
		sstr >> end;

		intervals.push_back(pair<int, int>(start, end));
	}
}

// DEBUG

void WriteVectorOfIntervals(vector<Point>& points)
{
	for (auto point : points)
	{
		if (point.isStart)
		{
			cout << "Start at " << point.pos;
		}
		else
		{
			cout << "End at " << point.pos;
		}
		cout << "\n";
	}
	cout << "\n";
}
