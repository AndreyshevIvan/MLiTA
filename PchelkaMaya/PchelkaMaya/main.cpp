#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

const char FRIEND = 'D';
const char MAYA = 'M';
const char ENEMY = 'V';

struct Node
{
	char type;
	int stepsCount = 0;
	bool isChecked = false;

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
void ReadBeehive(ifstream& file, vector<vector<Node>>& beehive);
int GetBestStepsCount(vector<vector<Node>> const& beehiveToSearch);
void MarkStepsFromNode(Node& node, int& finishStep);
void CheckNode(queue<Node*>& nodesToCheck, Node* node, bool& isFinish, int& finishStep);

// DEBUG
void WriteBeehive(vector<vector<Node>> const& beehive, bool isWriteLinks);
void WriteNode(Node const& node, bool isWriteLinks);


int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ifstream input("input.txt");
	ofstream output("output.txt");

	int levelsCount = GetLevelsCount(input);
	vector<vector<Node>> beehive;
	CreateEmptyBeehive(beehive, levelsCount);

	ReadBeehive(input, beehive);
	CreateLinksInBeehive(beehive);

	output << GetBestStepsCount(beehive);

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
}

void CreateLinksInBeehive(vector<vector<Node>>& beehive)
{
	size_t levelsCount = beehive.front().size();
	size_t centerAdress = levelsCount - 1;

	for (size_t i = 0; i < centerAdress; i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			beehive[i][j].bottomLeft = &beehive[i + 1][j];
			beehive[i][j].bottomRight = &beehive[i + 1][j + 1];

			beehive[i + 1][j].topRight = &beehive[i][j];
			beehive[i + 1][j + 1].topLeft = &beehive[i][j];

			if (j != 0)
			{
				beehive[i][j].left = &beehive[i][j - 1];
			}
			if (j != beehive[i].size() - 1)
			{
				beehive[i][j].right = &beehive[i][j + 1];
			}
		}
	}

	for (size_t i = centerAdress; i < 2 * centerAdress; i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			if (j != 0)
			{
				beehive[i][j].bottomLeft = &beehive[i + 1][j - 1];
				
				beehive[i][j].left = &beehive[i][j - 1];
			}
			if (j != beehive[i].size() - 1)
			{
				beehive[i][j].bottomRight = &beehive[i + 1][j];

				beehive[i + 1][j].topLeft = &beehive[i][j];
				beehive[i + 1][j].topRight = &beehive[i][j + 1];

				beehive[i][j].right = &beehive[i][j + 1];
			}
		}
	}

	for (size_t i = 1; i < levelsCount; i++)
	{
		beehive[2 * centerAdress][i].left = &beehive[2 * centerAdress][i - 1];
	}
	for (size_t i = 0; i < levelsCount - 1; i++)
	{
		beehive[2 * centerAdress][i].right = &beehive[2 * centerAdress][i + 1];
	}
}

void ReadBeehive(ifstream& input, vector<vector<Node>>& beehive)
{
	string beehiveRow;
	char type;

	for (size_t i = 0; i < beehive.size(); i++)
	{
		getline(input, beehiveRow);
		stringstream stream(beehiveRow);

		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			stream >> type;
			beehive[i][j].type = type;
		}
	}
}

int GetBestStepsCount(vector<vector<Node>> const& beehiveToSearch)
{
	auto beehive = beehiveToSearch;
	int finishStep = 0;

	for (size_t i = 0; i < beehive.size(); i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			if ((i == 0) ||
				(i == (beehive.size() - 1)) ||
				(j == 0) ||
				(j == beehive[i].size() - 1))
			{
				if (beehive[i][j].type != ENEMY)
				{
					MarkStepsFromNode(beehive[i][j], finishStep);

					if (finishStep == 39)
					{
						WriteBeehive(beehiveToSearch, false);
					}
				}
			}
		}
	}

	return finishStep;
}

void MarkStepsFromNode(Node& node, int& finishStep)
{
	node.stepsCount = 1;

	queue<Node*> nodesToCheck;
	nodesToCheck.push(&node);
	bool isFinish = false;

	while (!nodesToCheck.empty())
	{
		CheckNode(nodesToCheck, nodesToCheck.front(), isFinish, finishStep);
		nodesToCheck.pop();
	}
}

void CheckNode(queue<Node*>& nodesToCheck, Node* node, bool& isFinish, int& finishStep)
{
	int step = node->stepsCount;

	if (node->type != ENEMY && !isFinish)
	{
		if (node->type != MAYA)
		{
			if (node->left && !node->left->isChecked)
			{
				node->left->stepsCount = step + 1;
				node->left->isChecked = true;
				nodesToCheck.push(node->left);
			}
			if (node->right && !node->right->isChecked)
			{
				node->right->stepsCount = step + 1;
				node->right->isChecked = true;
				nodesToCheck.push(node->right);
			}
			if (node->topLeft && !node->topLeft->isChecked)
			{
				node->topLeft->stepsCount = step + 1;
				node->topLeft->isChecked = true;
				nodesToCheck.push(node->topLeft);
			}
			if (node->topRight && !node->topRight->isChecked)
			{
				node->topRight->stepsCount = step + 1;
				node->topRight->isChecked = true;
				nodesToCheck.push(node->topRight);
			}
			if (node->bottomLeft && !node->bottomLeft->isChecked)
			{
				node->bottomLeft->stepsCount = step + 1;
				node->bottomLeft->isChecked = true;
				nodesToCheck.push(node->bottomLeft);
			}
			if (node->bottomRight && !node->bottomRight->isChecked)
			{
				node->bottomRight->stepsCount = step + 1;
				node->bottomRight->isChecked = true;
				nodesToCheck.push(node->bottomRight);
			}
		}
		else
		{
			finishStep = node->stepsCount;
			isFinish = true;
		}
	}
}

// DEBUG

void WriteBeehive(vector<vector<Node>> const& beehive, bool isWriteLinks)
{
	for (size_t i = 0; i < beehive.size(); i++)
	{
		for (size_t j = 0; j < beehive[i].size(); j++)
		{
			WriteNode(beehive[i][j], isWriteLinks);
		}
		cout << endl;
	}
}
void WriteNode(Node const& node, bool isWriteLinks)
{
	cout << '[';

	cout << node.type;
	if (node.stepsCount >= 10)
	{
		cout << "," << node.stepsCount;
	}
	else
	{
		cout << ", " << node.stepsCount;
	}

	if (isWriteLinks)
	{
		if (node.left)  cout << "|L|";
		if (node.topLeft)  cout << "|TL|";
		if (node.topRight)  cout << "|TR|";
		if (node.right)  cout << "|R|";
		if (node.bottomRight)  cout << "|BR|";
		if (node.bottomLeft)  cout << "|BL|";
	}
	cout << ']';
}
