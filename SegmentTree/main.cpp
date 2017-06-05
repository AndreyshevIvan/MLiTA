#include "ReadPrint.h"
#include "SegmentTree.h"

int main()
{
	std::vector<int> input = ReadInput();
	CSegmentTree tree(input);
	(void)tree;

	return 0;
}
