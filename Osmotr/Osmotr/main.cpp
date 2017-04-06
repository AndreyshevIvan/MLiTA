#include "stdafx.h"
#include "Node.h"

using namespace std;

const size_t ARGUMENTS_COUNT = 2;
const string GOOD_MESSAGE = "YES";
const string BAD_MESSAGE = "NO";

void ReadNodes(ifstream &input, set<Node*> &nodes);

bool SearchLine(size_t &lineMark, set<Node*> &nodes);
void MarkCollum(size_t mark, set<Node*> &nodes);
void WriteMarkQueue(const vector<size_t> &markQueue);

int main(int argc, char* argv[])
{
	if (argc < ARGUMENTS_COUNT)
	{
		return 1;
	}

	ifstream input(argv[1]);
	set<Node*> allNodes;

	ReadNodes(input, allNodes);

	bool isSearchEnd = false;
	
	size_t mark = 0;
	vector<size_t> passQueue;
	set<Node*> toPass = allNodes;
	
	while (SearchLine(mark, toPass))
	{
		MarkCollum(mark, toPass);
		passQueue.push_back(mark);

		if (passQueue.size() == allNodes.size())
		{
			isSearchEnd = true;
			break;
		}
	}

	if (isSearchEnd)
	{
		cout << GOOD_MESSAGE << endl;
		WriteMarkQueue(passQueue);
	}
	else
	{
		cout << BAD_MESSAGE;
	}

	return 0;
}

void ReadNodes(ifstream &input, set<Node*> &nodes)
{
	string line;
	getline(input, line);
	stringstream sstr(line);

	size_t nodesCount = 0;
	size_t nodeNumber = 0;
	sstr >> nodesCount;

	while (nodeNumber < nodesCount)
	{
		Node* node = new Node;
		node->number = nodeNumber + 1;

		string nodeLine;
		getline(input, nodeLine);
		stringstream stream(nodeLine);

		size_t needToPassCount;
		stream >> needToPassCount;

		while (needToPassCount > 0)
		{
			size_t needToPassNode;
			stream >> needToPassNode;

			node->needToPass.insert(needToPassNode);
			needToPassCount--;
		}

		nodes.insert(node);
		nodeNumber++;
	}
}

bool SearchLine(size_t &lineMark, set<Node*> &nodes)
{
	for each (Node* node in nodes)
	{
		if (node->needToPass.size() == 0)
		{
			lineMark = node->number;
			nodes.erase(node);

			return true;
		}
	}

	return false;
}
void MarkCollum(size_t mark, set<Node*> &nodes)
{
	for each (Node* node in nodes)
	{
		if (node->needToPass.find(mark) != node->needToPass.end())
		{
			node->needToPass.erase(mark);
		}
	}
}

void WriteMarkQueue(const vector<size_t> &markQueue)
{
	for each (size_t markInQueue in markQueue)
	{
		cout << markInQueue << endl;
	}
}