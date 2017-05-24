#include "ReadPrint.h"
#include <algorithm>

void BuildTree(std::vector<int> &tree, std::vector<int> arr, int v, int tl, int tr);
int Sum(const std::vector<int> &tree, int v, int tl, int tr, int l, int r);
void Update(std::vector<int> &tree, int v, int tl, int tr, int pos, int newValue);

void EnterProcess(std::vector<int> &tree, int maxN);

int main()
{
	auto input = ReadInput();
	std::vector<int> tree(input.size() * 4);
	int maxN = input.size() - 1;
	WriteArray(input);
	BuildTree(tree, input, 1, 0, maxN);


	//int res1 = Sum(tree, 1, 0, maxN, 2, 4);
	//Update(tree, 1, 0, maxN, 3, -5);
	//Update(tree, 1, 0, maxN, 5, -1);
	//int res2 = Sum(tree, 1, 0, maxN, 2, 6);
	//int res3 = Sum(tree, 1, 0, maxN, 3, 3);

	//(void)res1;
	//(void)res2;
	//(void)res3;

	EnterProcess(tree, input.size() - 1);

	return 0;
}

void EnterProcess(std::vector<int> &tree, int maxN)
{
	std::string command;
	char ch = ' ';

	while (getline(std::cin, command))
	{
		std::stringstream stream(command);
		stream >> ch;
		if (ch == 'R')
		{
			size_t left;
			size_t right;
			stream >> left;
			stream >> right;
			WriteRsq(Sum(tree, 1, 0, maxN, left, right));
		}
		else if (ch == 'U')
		{
			size_t pos;
			size_t newValue;
			stream >> pos;
			stream >> newValue;
			WriteUpdate(pos, newValue);
			Update(tree, 1, 0, maxN, pos, newValue);
		}
		else
		{
			WriteError();
		}
	}
}

void BuildTree(std::vector<int> &tree, std::vector<int> arr, int v, int tl, int tr)
{
	if (tl == tr)
	{
		tree[v] = arr[tl];
	}
	else
	{
		int tm = (tl + tr) / 2;
		BuildTree(tree, arr, v * 2, tl, tm);
		BuildTree(tree, arr, v * 2 + 1, tm + 1, tr);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
}

int Sum(const std::vector<int> &tree, int v, int tl, int tr, int l, int r)
{
	if (l > r)
	{
		return 0;
	}
	if (l == tl && r == tr)
	{
		return tree[v];
	}

	int tm = (tl + tr) / 2;
	int first = Sum(tree, v * 2, tl, tm, l, std::min(r, tm));
	int second = Sum(tree, v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);

	return first + second;
}

void Update(std::vector<int> &tree, int v, int tl, int tr, int pos, int newValue)
{
	if (tl == tr)
	{
		tree[v] += newValue;
	}
	else
	{
		int tm = (tl + tr) / 2;
		if (pos <= tm)
		{
			Update(tree, v * 2, tl, tm, pos, newValue);
		}
		else
		{
			Update(tree, v * 2 + 1, tm + 1, tr, pos, newValue);
		}

		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
}