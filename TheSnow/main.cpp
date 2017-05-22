#include <fstream>
#include <string>
#include <sstream>
#include "SegmentTree.h"

void EnterProcess(std::ifstream &input, std::ofstream &output, CSegemntTree tree);
void ReadInput(std::ifstream &input, int &columnCount, int &commandsCount);

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	int columnCount;
	int commandsCount;

	ReadInput(input, columnCount, commandsCount);
	std::vector<int> arr(columnCount - 1, 0);
	CSegemntTree tree(arr);

	EnterProcess(input, output, tree);
}

void EnterProcess(std::ifstream &input, std::ofstream &output, CSegemntTree tree)
{
	(void)input;
	(void)output;
	(void)tree;
}

void ReadInput(std::ifstream &input, int &columnCount, int &commandsCount)
{
	std::string inputLine;
	getline(input, inputLine);
	std::stringstream stream(inputLine);

	stream >> columnCount;
	stream >> commandsCount;
}