#include "DiggersGold.h"
#include <iostream>

CDiggersGold::CDiggersGold(const std::vector<short> &items, size_t maxWeight)
{
	m_weight = maxWeight;
	m_items = items;
	Build();
}

std::vector<short> CDiggersGold::GetResult()
{
	size_t weight = m_weight;
	std::vector<short> result;

	if (m_build[weight].itemsCount == UNDEFINED)
	{
		return {};
	}

	while (weight != 0)
	{
		auto itemNumber = m_build[weight].used;
		result.push_back(itemNumber);
		weight -= m_items[itemNumber - 1];
	}

	return result;
}

void CDiggersGold::Build()
{
	m_build = std::vector<BuildNode>(m_weight + 1, { UNDEFINED, UNDEFINED });
	m_build[0] = { 0, UNDEFINED };

	for (int i = int(m_items.size()) - 1; i >= 0; i--)
	{
		std::cout << i << std::endl;
		for (int j = m_weight - m_items[i]; j >= 0; j--)
		{
			std::cout << j << std::endl;
			auto current = &m_build[j];
			auto newNode = &m_build[j + m_items[i]];

			if (current->itemsCount == UNDEFINED ||
				newNode->itemsCount != UNDEFINED)
			{
				continue;
			}

			newNode->itemsCount = current->itemsCount + 1;
			newNode->used = i + 1;
		}
	}
}