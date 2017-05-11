#include "ReadPrint.h"

void InitTree(std::vector<int> &tree, const std::vector<int> &arr);
void Update(std::vector<int> &tree, int i, int delta);
int Rsq(std::vector<int> &tree, int l, int r);
int Sum(std::vector<int> &tree, int r);

int main()
{
	auto arr = ReadInput();
	std::vector<int> fenwickTree;
	InitTree(fenwickTree, arr);

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
			WriteRsq(Rsq(fenwickTree, left, right));
		}
		else if (ch == 'U')
		{
			size_t pos;
			size_t delta;
			stream >> pos;
			stream >> delta;
			WriteUpdate(pos, delta);
			Update(fenwickTree, pos, delta);
		}
	}

	return 0;
}	

void InitTree(std::vector<int> &tree, const std::vector<int> &arr)
{
	tree = std::vector<int>(arr.size(), 0);

	for (size_t i = 0; i < arr.size(); i++)
	{
		Update(tree, i, arr[i]);
	}
}
void Update(std::vector<int> &tree, int i, int delta)
{
	for (; (size_t)i < tree.size(); i = (size_t)(i | (i + 1)))
	{
		tree[(size_t)i] += delta;
	}
}

int Rsq(std::vector<int> &tree, int l, int r)
{
	return Sum(tree, r) - Sum(tree, l - 1);
}
int Sum(std::vector<int> &tree, int r)
{
	int result = 0;

	for (; r >= 0; r = (r & (r + 1)) - 1)
	{
		result += tree[r];
	}

	return result;
}