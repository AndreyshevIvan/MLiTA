#include "DiggersGold.h"

CDiggersGold::CDiggersGold()
{
	m_items = { UNDEFINED };
}

void CDiggersGold::AddGold(unsigned short value)
{
	m_items.push_back(value);
}

std::vector<unsigned short> CDiggersGold::GetEqualPack(size_t maxWeight) const
{
	auto build = GetBuildContainer(maxWeight);
	size_t maxValue = 0;

	for (int i = 1; i < (int)build.size(); i++)
	{
		for (int j = 1; j < (int)build.front().size(); j++)
		{
			if (j < m_items[i])
			{
				build[i][j].weight = build[i - 1][j].weight;
				build[i][j].pack = build[i - 1][j].pack;
				continue;
			}

			auto withoutNext = build[i - 1][j - m_items[i]].weight + m_items[i];
			auto prev = build[i - 1][j].weight;

			if (withoutNext > prev)
			{
				build[i][j].weight = withoutNext;
				if (build[i][j].weight > maxValue)
				{
					build[i][j].pack = new std::vector<unsigned short>(*build[i - 1][j - m_items[i]].pack);
					build[i][j].pack->push_back(m_items[i]);
					maxValue = build[i][j].weight;
				}
				else
				{
					build[i][j].pack = build[i - 1][j - m_items[i]].pack;
				}
			}
			else
			{
				build[i][j].weight = build[i - 1][j].weight;
				build[i][j].pack = build[i - 1][j].pack;
			}

			if (build[i][j].weight == maxWeight)
			{
				return *build[i][j].pack;
			}
		}
	}

	return{};
}

BuildContainer CDiggersGold::GetBuildContainer(size_t maxWeight) const
{
	auto result = std::vector<std::vector<GoldNode>>(m_items.size());

	for (auto &row : result)
	{
		row = std::vector<GoldNode>(maxWeight + 1);
		row.front().pack = new std::vector<unsigned short>;
		row.front().weight = UNDEFINED;
	}

	for (auto &firstRowItem : result.front())
	{
		firstRowItem.weight = UNDEFINED;
		firstRowItem.pack = new std::vector<unsigned short>;
	}

	return result;
}
