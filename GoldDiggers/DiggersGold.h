#pragma once
#include <vector>
#include <algorithm>

enum
{
	UNDEFINED = 0,
};

struct GoldNode
{
	int weight;
	std::vector<size_t> pack;

	void Add(int newItem)
	{
		pack.push_back(newItem);
	}
};

typedef std::vector<std::vector<GoldNode>> BuildContainer;

class CDiggersGold
{
public:
	CDiggersGold();

	void AddGold(size_t value);
	std::vector<size_t> GetEqualPack(size_t maxWeight) const;

private:
	BuildContainer Build(size_t maxWeight) const;
	BuildContainer GetBuildContainer(size_t maxWeight) const;

	std::vector<int> m_items;

};

