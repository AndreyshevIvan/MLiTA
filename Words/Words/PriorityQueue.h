#pragma once
#include <string>
#include <queue>

using namespace std;

struct Comparator
{
	bool operator ()(const string &first, const string &second)
	{
		if (first.length() != second.length())
		{
			return (first.length() < second.length());
		}

		return (first > second);
	}
};

typedef priority_queue<string, vector<string>, Comparator> PriorityQueue;