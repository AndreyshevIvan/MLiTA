#include "DiggersGold.h"

CDiggersGold::CDiggersGold()
{
	m_items = { UNDEFINED };
}

void CDiggersGold::AddGold(size_t value)
{
	m_items.push_back(value);
}

std::vector<size_t> CDiggersGold::GetEqualPack(size_t maxWeight) const
{
	auto build = Build(maxWeight);

	for (const auto &row : build)
	{
		for (const auto &node : row)
		{
			if (node.weight == maxWeight)
			{
				return node.pack;
			}
		}
	}

	return {};
}

BuildContainer CDiggersGold::Build(size_t maxWeight) const
{
	auto build = GetBuildContainer(maxWeight);

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
				build[i][j].pack = build[i - 1][j - m_items[i]].pack;
				if (build[i][j].weight < (int)maxWeight)
				{
					build[i][j].Add(withoutNext);
				}
				continue;
			}

			build[i][j].weight = prev;
			build[i][j].pack = build[i - 1][j].pack;
		}
	}

	return build;
}

BuildContainer CDiggersGold::GetBuildContainer(size_t maxWeight) const
{
	auto result = std::vector<std::vector<GoldNode>>(m_items.size());

	for (auto &row : result)
	{
		row = std::vector<GoldNode>(maxWeight + 1);
	}

	return result;
}
