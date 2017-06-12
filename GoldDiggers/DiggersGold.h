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
	std::vector<unsigned short>* pack;
};

typedef std::vector<std::vector<GoldNode>> BuildContainer;

class CDiggersGold
{
public:
	CDiggersGold();

	void AddGold(unsigned short value);
	std::vector<unsigned short> GetEqualPack(size_t maxWeight) const;

private:
	BuildContainer GetBuildContainer(size_t maxWeight) const;

	std::vector<unsigned short> m_items;

};

