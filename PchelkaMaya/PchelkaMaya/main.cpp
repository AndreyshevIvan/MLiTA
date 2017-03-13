#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
	// 'D' - сота друга
	// 'M' - сота Майи
	// 'V' - сота врага
	char type;

	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};

void ReadBeehive(int& levelsCount, vector<vector<Node>>& beehive);

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ifstream input("input.txt");
	ofstream output("output.txt");



	return 0;
}

void ReadBeehive(int& levelsCount, vector<vector<Node>>& beehive)
{
	(void)levelsCount;
	(void)beehive;
}
