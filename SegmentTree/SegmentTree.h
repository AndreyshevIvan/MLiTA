#pragma once
#include <vector>
#include <algorithm>

class CSegmentTree
{
public:
	CSegmentTree(const std::vector<int> &arr);

	long long Sum();
	void Modify();

private:
	void Build(const std::vector<int> &arr, int v, int vl, int vr);

	size_t m_maxIndex;
	std::vector<int> m_tree;

};