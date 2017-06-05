#include "SegmentTree.h"

CSegmentTree::CSegmentTree(const std::vector<int> &arr)
{
	m_maxIndex = arr.size() - 1;
	m_tree = std::vector<int>(arr.size() * 4, 0);
}

long long CSegmentTree::Sum()
{
	return 0;
}

void CSegmentTree::Modify()
{

}

void CSegmentTree::Build(const std::vector<int> &arr, int v, int vl, int vr)
{

}