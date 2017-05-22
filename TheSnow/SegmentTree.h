#pragma once
#include <vector>
#include <map>
#include <algorithm>

class CSegemntTree
{
public:
	CSegemntTree(const std::vector<int> arr)
	{
		const size_t &arrSize = arr.size();
		m_tree = std::vector<int>(arrSize * 4, 0);
		m_maxIndex = arrSize - 1;
		Build(arr, 1, 0, m_maxIndex);
	}
	int GetMaxIndex() const
	{
		return m_maxIndex;
	}
	int GetSum(int cIndex, int tLeft, int tRight, int left, int right) const
	{
		if (left > right)
		{
			return 0;
		}
		if (left == tLeft && right == tRight)
		{
			return m_tree[cIndex];
		}

		int tMiddle = (tLeft + tRight) / 2;
		int rmMax = std::min(right, tMiddle);
		int lmMax = std::max(left, tMiddle + 1);
		int first = GetSum(cIndex * 2, tLeft, tMiddle, left, rmMax);
		int second = GetSum(cIndex * 2 + 1, tMiddle + 1, tRight, lmMax, right);

		return first + second;
	}
	void Add(int cIndex, int tLeft, int tRight, int updPos, int addValue)
	{
		if (tLeft == tRight)
		{
			m_tree[cIndex] += addValue;
		}
		else
		{
			int tm = (tLeft + tRight) / 2;
			if (updPos <= tm)
			{
				Add(cIndex * 2, tLeft, tm, updPos, addValue);
			}
			else
			{
				Add(cIndex * 2 + 1, tm + 1, tRight, updPos, addValue);
			}

			m_tree[cIndex] = m_tree[cIndex * 2] + m_tree[cIndex * 2 + 1];
		}
	}
protected:
	void Build(const std::vector<int> &arr, int cIndex, int tLeft, int tRight)
	{
		if (tLeft == tRight)
		{
			m_tree[cIndex] = arr[tLeft];
		}
		else
		{
			int tm = (tLeft + tRight) / 2;
			Build(arr, cIndex * 2, tLeft, tm);
			Build(arr, cIndex * 2 + 1, tm + 1, tRight);
			m_tree[cIndex] = m_tree[cIndex * 2] + m_tree[cIndex * 2 + 1];
		}
	}

	int m_maxIndex;
	std::vector<int> m_tree;
};