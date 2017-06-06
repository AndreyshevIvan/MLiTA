#pragma once
#include <vector>
#include <algorithm>
#include "PowerLine.h"

enum
{
	UNDEFINED = -1,

	// Commands
	ADD_SNOW = 1,
	GET_SNOW_COUNT,
};

namespace
{
	struct Segment
	{
		int value;
		int extra;
		long long sum;
	};
}

class CSegementTree : public IPowerLine
{
public:
	CSegementTree(size_t segmentsCount)
	{
		m_segmentsCount = segmentsCount;
		std::vector<int> startArr(m_segmentsCount + 1, 0);
		m_tree = std::vector<Segment>(m_segmentsCount * 4);
		Build(1, m_segmentsCount, 1, startArr);
	}

	long long GetSnowSum(size_t leftCollumn, size_t rightColumn) const override
	{
		return Rsq(leftCollumn, rightColumn - 1, 1, m_segmentsCount, 1);
	}

	void AddSnow(size_t leftColumn, size_t rightColumn, int snowCount) override
	{
		Add(leftColumn, rightColumn - 1, snowCount, 1, m_segmentsCount, 1);
	}

private:
	void Build(int left, int right, int pos, const std::vector<int> &arr)
	{
		if (left == right)
		{
			m_tree[pos] = { arr[left], 0, arr[left] };
			return;
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		Build(left, leftEnd, leftPos, arr);
		Build(rightBegin, right, rightPos, arr);

		long long newSum = m_tree[leftPos].sum + m_tree[rightPos].sum;
		m_tree[pos] = { UNDEFINED , 0, newSum };
	}
	void Update(int qLeft, int qRight, int qValue, int left, int right, int pos)
	{
		if (qRight < left || right < qLeft)
		{
			return;
		}
		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);
		if (qLeft == left && qRight == right)
		{
			m_tree[pos] = { qValue, 0, qValue * (right - left + 1) };
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
	}
	void Add(int qLeft, int qRight, int qExtra, int left, int right, int pos)
	{
		if (qRight < left || right < qLeft)
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
	}
	long long Rsq(int qLeft, int qRight, int left, int right, int pos) const
	{
		if (qRight < left || right < qLeft)
		{
			return 0;
		}

		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);

		if (qLeft == left && qRight == right)
		{
			return m_tree[pos].sum + long long(m_tree[pos].extra) * (right - left + 1);
		}

		if (m_tree[pos].value != UNDEFINED)
		{
			return long long(m_tree[pos].value + m_tree[pos].extra) * (qRight - qLeft + 1);
		}

		int leftEnd = (left + right) / 2;
		int rightBegin = leftEnd + 1;
		int leftPos = pos * 2;
		int rightPos = leftPos + 1;

		long long leftSum = Rsq(qLeft, qRight, left, leftEnd, leftPos);
		long long rightSum = Rsq(qLeft, qRight, rightBegin, right, rightPos);
		return (leftSum + rightSum) + long long(m_tree[pos].extra) * (qRight - qLeft + 1);
	}

	size_t m_segmentsCount;
	std::vector<Segment> m_tree;

};