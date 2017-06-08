#pragma once
#include <vector>
#include <string>

class CBigNumber
{
public:
	CBigNumber(const std::string &numberStr);

private:
	std::vector<size_t> m_digits;
	size_t m_size;

};