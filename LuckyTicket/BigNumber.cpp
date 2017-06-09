#include "BigNumber.h"

#include <algorithm>

namespace
{
	const char* EMPTY_STR = "CBigNumber: create from empty string is not allowed.";
}

CBigNumber::CBigNumber(size_t number)
{
	this->CBigNumber::CBigNumber(std::to_string(number));
}

CBigNumber::CBigNumber(const std::string &numberStr)
{
	if (numberStr.empty())
	{
		throw std::exception(EMPTY_STR);
	}

	for (int i = numberStr.size() - 1; i >= 0; i--)
	{
		auto digit = numberStr[i];
		m_digits.push_back((unsigned short)std::atoi(&digit));
	}
}

CBigNumber::CBigNumber(const CBigNumber &bigNumber)
{
	m_digits = bigNumber.GetDigits();
}

CBigNumber::CBigNumber(const Digits &digits)
{
	m_digits = digits;
}

Digits CBigNumber::GetDigits() const
{
	return m_digits;
}

size_t CBigNumber::Length() const
{
	return m_digits.size();
}

size_t CBigNumber::DigitsSum() const
{
	size_t result = 0;
	for (auto digit : m_digits)
	{
		result += digit;
	}

	return result;
}

std::string CBigNumber::ToString() const
{
	std::string result;

	for (int i = this->Length() - 1; i >= 0; i--)
	{
		result += std::to_string(m_digits[i]);
	}

	return result;
}