#pragma once
#include <vector>
#include <algorithm>

namespace
{
	const int UNDEFINED = -1;
}

struct Segment
{
	int value;
	int extra;
	long long sum;
	int min;
};

class CSegmentTree
{
public:
	CSegmentTree::CSegmentTree(const std::vector<int> &startArr)
	{
		m_arraySize = startArr.size() - 1;
		m_tree = std::vector<Segment>(m_arraySize * 4);
		Build(1, m_arraySize, 1, startArr);
	}
	int CSegmentTree::Get(size_t position)
	{
		return Get(position, 1, m_arraySize, 1);
	}
	long long Rsq(size_t from, size_t to)
	{
		return Rsq(from, to, 1, m_arraySize, 1);
	}
	int Rmq(size_t from, size_t to)
	{
		return Rmq(from, to, 1, m_arraySize, 1);
	}
	void Update(size_t from, size_t to, int newValue)
	{
		Update(from, to, newValue, 1, m_arraySize, 1);
	}
	void Add(size_t from, size_t to, int addValue)
	{
		Add(from, to, addValue, 1, m_arraySize, 1);
	}

private:
	void CSegmentTree::Build(int left, int right, int pos, const std::vector<int> &arr)
	{
		if (left == right)
		{
			m_tree[pos] = { arr[left], 0, arr[left], arr[left] };
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		Build(left, leftEnd, leftPos, arr);
		Build(rightBegin, right, rightPos, arr);

		long long newSum = m_tree[leftPos].sum + m_tree[rightPos].sum;
		int newMin = std::min(m_tree[leftPos].min, m_tree[rightPos].min);
		m_tree[pos] = { UNDEFINED , 0, newSum, newMin };
	}

	int CSegmentTree::Get(int qPos, int left, int right, int pos)
	{
		if (m_tree[pos].value != UNDEFINED)
		{
			return m_tree[pos].value + m_tree[pos].extra;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		if (qPos <= leftEnd)
		{
			return Get(qPos, left, leftEnd, leftPos) + m_tree[pos].extra;
		}

		return Get(qPos, rightBegin, right, rightPos) + m_tree[pos].extra;
	}

	void Update(int qLeft, int qRight, int qValue, int left, int right, int pos)
	{
		if (qRight < qLeft || right < left)
		{
			return;
		}
		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);
		if (qLeft == left && qRight == right)
		{
			m_tree[pos] = { qValue, 0, qValue, qValue * (right - left + 1) };
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		if (m_tree[pos].value != UNDEFINED)
		{
			Update(left, leftEnd, m_tree[pos].value + m_tree[pos].extra, left, leftEnd, leftPos);
			Update(rightBegin, right, m_tree[pos].value + m_tree[pos].extra, rightBegin, right, rightPos);
			m_tree[pos].value = UNDEFINED;
			m_tree[pos].extra = 0;
		}

		if (m_tree[pos].extra != 0)
		{
			Add(left, leftEnd, m_tree[pos].extra, left, leftEnd, leftPos);
			Add(rightBegin, right, m_tree[pos].extra, rightBegin, right, rightPos);
			m_tree[pos].extra = 0;
		}

		Update(qLeft, qRight, qValue, left, leftEnd, leftPos);
		Update(qLeft, qRight, qValue, rightBegin, right, rightPos);
		m_tree[pos].sum = m_tree[leftPos].sum + m_tree[rightPos].sum;
		m_tree[pos].min = std::min(m_tree[leftPos].min, m_tree[rightPos].min);
	}
	
	void Add(int qLeft, int qRight, int qExtra, int left, int right, int pos)
	{
		if (qRight < qLeft || right < left)
		{
			return;
		}
		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);
		if (qLeft == left && qRight == right)
		{
			m_tree[pos].extra += qExtra;
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		if (m_tree[pos].value != UNDEFINED)
		{
			Update(left, leftEnd, m_tree[pos].value + m_tree[pos].extra, left, leftEnd, leftPos);
			Update(rightBegin, right, m_tree[pos].value + m_tree[pos].extra, rightBegin, right, rightPos);
			m_tree[pos].value = UNDEFINED;
			m_tree[pos].extra = 0;
		}

		if (m_tree[pos].extra != 0)
		{
			Add(left, leftEnd, m_tree[pos].extra, left, leftEnd, leftPos);
			Add(rightBegin, right, m_tree[pos].extra, rightBegin, right, rightPos);
			m_tree[pos].extra = 0;
		}

		Add(qLeft, qRight, qExtra, left, leftEnd, leftPos);
		Add(qLeft, qRight, qExtra, rightBegin, right, rightPos);

		long long leftSum = m_tree[leftPos].sum + (leftEnd - left + 1) * m_tree[leftPos].extra;
		long long rightSum = m_tree[rightPos].sum + (right - rightBegin + 1) * m_tree[rightPos].extra;
		m_tree[pos].sum = leftSum + rightSum;

		int lValue = m_tree[leftPos].min + m_tree[leftPos].extra;
		int rValue = m_tree[rightPos].min + m_tree[rightPos].extra;
		m_tree[pos].min = std::min(lValue, rValue);
	}

	long long Rsq(int qLeft, int qRight, int left, int right, int pos)
	{
		if (qRight < qLeft || right < left)
		{
			return 0;
		}
		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);
		if (qLeft == left && qRight == right)
		{
			return m_tree[pos].sum + m_tree[pos].extra * (right - left + 1);
		}

		if (m_tree[pos].value != UNDEFINED)
		{
			return (m_tree[pos].value + m_tree[pos].extra) * (qRight - qLeft + 1);
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		long long leftSum = Rsq(qLeft, qRight, left, leftEnd, leftPos);
		long long rightSum = Rsq(qLeft, qRight, rightBegin, right, rightPos);
		return (leftSum + rightSum) + m_tree[pos].extra * (qRight - qLeft + 1);
	}

	int Rmq(int qLeft, int qRight, int left, int right, int pos)
	{
		if (qRight < qLeft || right < left)
		{
			return INT_MAX;
		}
		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);
		if (qLeft == left && qRight == right)
		{
			return m_tree[pos].min + m_tree[pos].extra;
		}

		if (m_tree[pos].value != UNDEFINED)
		{
			return m_tree[pos].min + m_tree[pos].extra;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		int leftMin = Rmq(qLeft, qRight, left, leftEnd, leftPos);
		int rightMin = Rmq(qLeft, qRight, rightBegin, right, rightPos);
		return std::min(leftMin, rightMin) + m_tree[pos].extra;
	}

	std::vector<Segment> m_tree;
	size_t m_arraySize;
	size_t m_maxIndex;
};