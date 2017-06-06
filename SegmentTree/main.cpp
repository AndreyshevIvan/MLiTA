#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <climits>
#include <iostream>

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
	CSegmentTree(const std::vector<int> &startArr)
	{
		m_arraySize = startArr.size() - 1;
		m_tree = std::vector<Segment>(m_arraySize * 4);
		Build(1, m_arraySize, 1, startArr);
	}
	int Get(size_t position)
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
	void Build(int left, int right, int pos, const std::vector<int> &arr)
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

	int Get(int qPos, int left, int right, int pos)
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
		if (qRight < left || right < qLeft)
		{
			return;
		}
		qLeft = std::max(qLeft, left);
		qRight = std::min(qRight, right);
		if (qLeft == left && qRight == right)
		{
			m_tree[pos] = { qValue, 0, qValue * (right - left + 1), qValue };
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

		int lValue = m_tree[leftPos].min + m_tree[leftPos].extra;
		int rValue = m_tree[rightPos].min + m_tree[rightPos].extra;
		m_tree[pos].min = std::min(lValue, rValue);
	}

	long long Rsq(int qLeft, int qRight, int left, int right, int pos)
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

	int Rmq(int qLeft, int qRight, int left, int right, int pos)
	{
		if (qRight < left || right < qLeft)
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

void Print(long long value);
void Process(CSegmentTree &tree);

int main()
{
	int segmentsCount;
	scanf("%d", &segmentsCount);
	std::vector<int> startArr(1 + segmentsCount);
	for (int i = 1; i <= segmentsCount; i++)
	{
		scanf("%d", &startArr[i]);
	}
	CSegmentTree tree(startArr);
	Process(tree);

	return 0;
}

void Process(CSegmentTree &tree)
{
	int commandsCount;
	scanf("%d", &commandsCount);
	for (int i = 0; i < commandsCount; i++)
	{
		char buffer[6 + 1];
		scanf("%6s", buffer);
		std::string command(buffer);
		if (command == "get")
		{
			int pos;
			scanf("%d", &pos);
			Print(tree.Get(pos));
		}
		else if (command == "update")
		{
			int from;
			int to;
			int value;
			scanf("%d %d %d", &from, &to, &value);
			tree.Update(from, to, value);
		}
		else if (command == "add")
		{
			int from;
			int to;
			int addValue;
			scanf("%d %d %d", &from, &to, &addValue);
			tree.Add(from, to, addValue);
		}
		else if (command == "rsq")
		{
			int from;
			int to;
			scanf("%d %d", &from, &to);
			Print(tree.Rsq(from, to));
		}
		else if (command == "rmq")
		{
			int from;
			int to;
			scanf("%d %d", &from, &to);
			Print(tree.Rmq(from, to));
		}
	}
}

void Print(long long value)
{
	printf("%lld\n", value);
}