#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Node
{
	// 'D' - Friend
	// 'M' - Maya
	// 'V' - Enemy
	char type;

	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};

int GetLevelsCount(ifstream& file);
void CreateEmptyBeehive(vector<vector<Node>>& beehive, int levelsCount);
void CreateLinksInBeehive(vector<vector<Node>>& beehive);
void ReadBeehive(ifstream& file, vector<vector<Node>>& beehive, int levelsCount);

// DEBUG
void WriteBeehive(vector<vector<Node>> const& beehive);
void WriteNode(Node const& node);


int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ifstream input("input.txt");
	ofstream output("output.txt");

	int levelsCount = GetLevelsCount(input);
	vector<vector<Node>> beehive;
	CreateEmptyBeehive(beehive, levelsCount);

	WriteBeehive(beehive);

	ReadBeehive(input, beehive, levelsCount);


	return 0;
}

int GetLevelsCount(ifstream& file)
{
	int levelsCount;
	string str;
	getline(file, str);
	stringstream sstr(str);
	sstr >> levelsCount;

	return levelsCount;
}

void CreateEmptyBeehive(vector<vector<Node>>& beehive, int levelsCount)
{
	int beeCount = 0;

	for (int i = 0; i < (2 * levelsCount - 1); i++)
	{
		vector<Node> beehiveRow;

		beeCount = (i < levelsCount) ? (levelsCount + i) : (beeCount - 1);
		for (int j = 0; j < beeCount; j++)
		{
			Node node;
			beehiveRow.push_back(node);
		}

		beehive.push_back(beehiveRow);
	}

	CreateLinksInBeehive(beehive);
}

void CreateLinksInBeehive(vector<vector<Node>>& beehive)
{
	size_t levelsCount = beehive.front().size();

	for (size_t i = 0; i < (levelsCount - 1); i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			beehive[i][j].bottomLeft = &beehive[i + 1][j];
			beehive[i][j].bottomRight = &beehive[i + 1][j + 1];

			if (j != 0)
			{
				beehive[i + 1][j].topLeft = &beehive[i][j];
			}
			if (j != beehive[i].size() - 1)
			{
				beehive[i + 1][j].topRight = &beehive[i][j + 1];
			}
		}
	}

	for (size_t i = levelsCount - 1; i < (2 * levelsCount - 2); i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			if (j != 0)
				beehive[i][j].bottomLeft = &beehive[i + 1][j - 1];
			if (j != beehive[i].size() - 1)
				beehive[i][j].bottomRight = &beehive[i + 1][j];

			if (j != beehive[i + 1].size())
			{
				beehive[i + 1][j].topLeft = &beehive[i][j];
				beehive[i + 1][j].topRight = &beehive[i][j + 1];
			}
		}
	}
}

void ReadBeehive(ifstream& file, vector<vector<Node>>& beehive, int levelsCount)
{
	(void)file;
	(void)levelsCount;
	(void)beehive;
}

// DEBUG

void WriteBeehive(vector<vector<Node>> const& beehive)
{
	for (size_t i = 0; i < beehive.size(); i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			WriteNode(beehive[i][j]);
		}
		cout << endl;
	}
}

void WriteNode(Node const& node)
{
	cout << '[';

	if (node.left)  cout << "|L|";
	if (node.topLeft)  cout << "|TL|";
	if (node.topRight)  cout << "|TR|";
	if (node.right)  cout << "|R|";
	if (node.bottomRight)  cout << "|BR|";
	if (node.bottomLeft)  cout << "|BL|";

	cout << ']';
}
