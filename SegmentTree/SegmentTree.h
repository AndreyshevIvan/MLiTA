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
		s = std::vector<Segment>(m_arraySize * 4);
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
			s[pos] = { arr[left], 0, arr[left], arr[left] };
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		Build(left, leftEnd, leftPos, arr);
		Build(rightBegin, right, rightPos, arr);

		long long newSum = s[leftPos].sum + s[rightPos].sum;
		int newMin = std::min(s[leftPos].min, s[rightPos].min);
		s[pos] = { UNDEFINED , 0, newSum, newMin };
	}

	int CSegmentTree::Get(int qPos, int left, int right, int pos)
	{
		if (s[pos].value != UNDEFINED)
		{
			return s[pos].value + s[pos].extra;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		if (qPos <= leftEnd)
		{
			return Get(qPos, left, leftEnd, leftPos) + s[pos].extra;
		}

		return Get(qPos, rightBegin, right, rightPos) + s[pos].extra;
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
			s[pos] = { qValue, 0, qValue, qValue * (right - left + 1) };
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		if (s[pos].value != UNDEFINED)
		{
			Update(left, leftEnd, s[pos].value + s[pos].extra, left, leftEnd, leftPos);
			Update(rightBegin, right, s[pos].value + s[pos].extra, rightBegin, right, rightPos);
			s[pos].value = UNDEFINED;
			s[pos].extra = 0;
		}

		if (s[pos].extra != 0)
		{
			Add(left, leftEnd, s[pos].extra, left, leftEnd, leftPos);
			Add(rightBegin, right, s[pos].extra, rightBegin, right, rightPos);
			s[pos].extra = 0;
		}

		Update(qLeft, qRight, qValue, left, leftEnd, leftPos);
		Update(qLeft, qRight, qValue, rightBegin, right, rightPos);
		s[pos].sum = s[leftPos].sum + s[rightPos].sum;
		s[pos].min = std::min(s[leftPos].min, s[rightPos].min);
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
			s[pos].extra += qExtra;
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		if (s[pos].value != UNDEFINED)
		{
			Update(left, leftEnd, s[pos].value + s[pos].extra, left, leftEnd, leftPos);
			Update(rightBegin, right, s[pos].value + s[pos].extra, rightBegin, right, rightPos);
			s[pos].value = UNDEFINED;
			s[pos].extra = 0;
		}

		if (s[pos].extra != 0)
		{
			Add(left, leftEnd, s[pos].extra, left, leftEnd, leftPos);
			Add(rightBegin, right, s[pos].extra, rightBegin, right, rightPos);
			s[pos].extra = 0;
		}

		Add(qLeft, qRight, qExtra, left, leftEnd, leftPos);
		Add(qLeft, qRight, qExtra, rightBegin, right, rightPos);

		long long leftSum = s[leftPos].sum + (leftEnd - left + 1) * s[leftPos].extra;
		long long rightSum = s[rightPos].sum + (right - rightBegin + 1) * s[rightPos].extra;
		s[pos].sum = leftSum + rightSum;

		int lValue = s[leftPos].min + s[leftPos].extra;
		int rValue = s[rightPos].min + s[rightPos].extra;
		s[pos].min = std::min(lValue, rValue);
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
			return s[pos].sum + s[pos].extra * (right - left + 1);
		}

		if (s[pos].value != UNDEFINED)
		{
			return (s[pos].value + s[pos].extra) * (qRight - qLeft + 1);
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		long long leftSum = Rsq(qLeft, qRight, left, leftEnd, leftPos);
		long long rightSum = Rsq(qLeft, qRight, rightBegin, right, rightPos);
		return (leftSum + rightSum) + s[pos].extra * (qRight - qLeft + 1);
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
			return s[pos].min + s[pos].extra;
		}

		if (s[pos].value != UNDEFINED)
		{
			return s[pos].min + s[pos].extra;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		int leftMin = Rmq(qLeft, qRight, left, leftEnd, leftPos);
		int rightMin = Rmq(qLeft, qRight, rightBegin, right, rightPos);
		return std::min(leftMin, rightMin) + s[pos].extra;
	}

	std::vector<Segment> s;
	size_t m_arraySize;
	size_t m_maxIndex;
};