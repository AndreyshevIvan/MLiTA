#include "BigNumber.h"

#include <algorithm>

namespace
{
	const char* EMPTY_STR = "CBigNumber: create from empty string is not allowed.";
}

CBigNumber::CBigNumber()
{
	m_digits.push_back(0);
	m_size = m_digits.size();
}

CBigNumber::CBigNumber(size_t number)
{
	std::string numberStr = std::to_string(number);
	auto fromStr = CBigNumber(numberStr);
	m_digits = fromStr.GetDigits();
	m_size = fromStr.Length();
}

CBigNumber::CBigNumber(const std::string &numberStr)
{
	if (numberStr.empty())
	{
		throw std::exception(EMPTY_STR);
	}

	m_size = numberStr.size();
	for (int i = m_size - 1; i >= 0; i--)
	{
		auto digit = numberStr[i];
		m_digits.push_back((unsigned short)std::atoi(&digit));
	}
}

CBigNumber::CBigNumber(const CBigNumber &bigNumber)
{
	m_digits = bigNumber.GetDigits();
	m_size = m_digits.size();
}

Digits CBigNumber::GetDigits() const
{
	return m_digits;
}

size_t CBigNumber::Length() const
{
	return m_digits.size();
}

std::string CBigNumber::ToString() const
{
	std::string result;

	for (int i = m_size - 1; i >= 0; i--)
	{
		result += std::to_string(m_digits[i]);
	}

	return result;
}