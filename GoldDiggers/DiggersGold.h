#pragma once
#include <vector>
#include <algorithm>

enum
{
	UNDEFINED = -1,
};

struct BuildNode
{
	int itemsCount;
	int used;
};

class CDiggersGold
{
public:
	CDiggersGold::CDiggersGold(const std::vector<short> &items, size_t maxWeight);
	std::vector<short> GetResult();

private:
	void Build();
	std::vector<BuildNode> m_build;
	std::vector<short> m_items;
	size_t m_weight;

};
