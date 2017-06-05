#include "SegmentTree.h"

CSegmentTree::CSegmentTree(size_t arraySize)
{
	m_maxIndex = arraySize - 1;
	m_tree = std::vector<int>(arraySize * 4, 0);
	m_tAdding = std::vector<int>(arraySize * 4, 0);
}

long long CSegmentTree::Sum(int v, int vl, int vr, int l, int r)
{
	Push(v, vl, vr);

	if (r < vl || vr < l)
	{
		return 0;
	}
	if (l <= vl && vr <= r)
	{
		return m_tree[v];
	}
	int vm = vl + (vr - vl) / 2;
	auto sumL = Sum(2 * v + 1, vl, vm, l, r);
	auto sumR = Sum(2 * v + 2, vm + 1, vr, l, r);
	return sumL + sumR;
}

void CSegmentTree::Modify(int v, int vl, int vr, int l, int r, int delta)
{
	Push(v, vl, vr);

	if (v < vl || vr < l)
	{
		return;
	}
	if (l <= vl && vr <= r)
	{
		m_tAdding[v] = delta;
		Push(v, vl, vr);
		return;
	}

	int vm = vl + (vr - vl) / 2;
	Modify(2 * v + 1, vl, vm, l, r, delta);
	Modify(2 * v + 2, vm + 1, vr, l, r, delta);
	m_tree[v] = m_tree[2 * v + 1] + m_tree[2 * v + 2];
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

void CSegmentTree::Push(int v, int vl, int vr)
{
	if (m_tAdding[v] != 0)
	{
		m_tree[v] += m_tAdding[v] * (vr - vl + 1);
		if (vl != vr)
		{
			m_tAdding[2 * v + 1] += m_tAdding[v];
			m_tAdding[2 * v + 2] += m_tAdding[v];
		}
		m_tAdding[v] = 0;
	}
}