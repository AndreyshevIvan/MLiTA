#include "ReadPrint.h"
#include "SegmentTree.h"

void Process(CSegmentTree tree);

int main()
{
	Process(CSegmentTree(10));

	return 0;
}

void Process(CSegmentTree tree)
{
	std::string command;
	int request = 0;

	while (getline(std::cin, command))
	{
		std::stringstream stream(command);
		stream >> request;
		if (request == 1)
		{
			size_t from;
			size_t to;
			stream >> from >> to;
			auto result = tree.Sum(0, 0, tree.GetMaxIndex(), from, to);
			WriteSum(result);
		}
		else if (request == 2)
		{
			size_t from;
			size_t to;
			size_t delta;
			stream >> from >> to >> delta;
			tree.Modify(0, 0, tree.GetMaxIndex(), from, to, delta);
			WriteUpdate(from, to, delta);
		}
	}
}
