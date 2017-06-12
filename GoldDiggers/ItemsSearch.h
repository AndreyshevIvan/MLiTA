#pragma once
#include <vector>

class CItemsSearch
{
public:
	CItemsSearch(const std::vector<size_t> &items);

	std::vector<size_t> GetEqualPack(size_t value) const;

private:
	void Build();
	void CreateEqual();

	std::vector<size_t> m_items;
	std::vector<size_t> m_addItems;
	std::vector<std::vector<size_t>> m_build;

};