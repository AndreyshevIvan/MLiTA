#pragma once
#include <vector>
#include <algorithm>

class CSegmentTree
{
public:
	CSegmentTree(size_t arraySize);

	long long Sum(int v, int vl, int vr, int l, int r);
	void Modify(int v, int vl, int vr, int l, int r, int delta);

	int GetMaxIndex()
	{
		return m_maxIndex;
	}

private:
	void Build(const std::vector<int> &arr, int v, int vl, int vr);
	void Push(int v, int vl, int vr);

	int m_maxIndex;
	std::vector<int> m_tree;
	std::vector<int> m_tAdding;

};