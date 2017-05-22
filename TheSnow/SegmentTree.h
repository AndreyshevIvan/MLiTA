#pragma once
#include <vector>
#include <map>

class CSegemntTree
{
public:
	CSegemntTree(const std::vector<int> arr)
	{
		m_tree = std::vector<int>(arr.size() * 4, 0);
		m_maxIndex = arr.size() - 1;
		Build(arr, 1, 0, m_maxIndex);
	}

	int GetMaxIndex()
	{
		return m_maxIndex;
	}

private:
	CSegemntTree()
	{
	}

	void Build(const std::vector<int> &arr, int v, int tLeft, int tRight)
	{
		if (tLeft == tRight)
		{
			m_tree[v] = arr[tLeft];
		}
		else
		{
			int tm = (tLeft + tRight) / 2;
			Build(arr, v * 2, tLeft, tm);
			Build(arr, v * 2 + 1, tm + 1, tRight);
			m_tree[v] = m_tree[v * 2] + m_tree[v * 2 + 1];
		}
	}

	int m_maxIndex;
	std::vector<int> m_tree;
};