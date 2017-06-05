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
	if (vl == vr)
	{
		m_tree[v] = arr[vl] - (vl ? arr[vl - 1] : 0);
		return;
	}

	int vm = vl + (vr - vl) / 2;
	Build(arr, 2 * v + 1, vl, vm);
	Build(arr, 2 * v + 2, vm + 1, vr);
	m_tree[v] = m_tree[2 * v + 1] + m_tree[2 * v + 2];
}