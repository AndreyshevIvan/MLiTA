#pragma once
#include <memory>
#include "SegmentTree.h"

enum Command
{
	ADD = 1,
	INFO,
};

class CPowerLine
{
public:
	CPowerLine(int columnCount)
	{
		std::vector<int> arr(columnCount - 1, 0);
		m_tree = std::make_unique<CSegemntTree>(arr);
	}

	void AddSnow(size_t leftColl, size_t rightColl, int snowCount)
	{
		auto maxI = m_tree->GetMaxIndex();
		for (size_t i = leftColl - 1; i < rightColl - 1; i++)
		{
			m_tree->Add(1, 0, maxI, i, snowCount);
		}
	}
	std::string GetInfo(size_t leftColl, size_t rightColl)
	{
		auto maxI = m_tree->GetMaxIndex();
		int result = m_tree->GetSum(1, 0, maxI, leftColl - 1, rightColl - 2);

		return std::to_string(result);
	}
private:
	std::unique_ptr<CSegemntTree> m_tree;
};