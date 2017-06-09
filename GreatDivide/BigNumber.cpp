#include "BigNumber.h"

#include <algorithm>
#include <stack>

namespace
{
	const char* EMPTY_STR = "CBigNumber: create from empty string is not allowed.";
}

CBigNumber::CBigNumber()
{
	m_digits.push_back(0);
	m_size = m_digits.size();
}

CBigNumber::CBigNumber(const std::string &numberStr)
{
	if (numberStr.empty())
	{
		throw std::exception(EMPTY_STR);
	}

	std::stack<unsigned short> digitStack;
	std::for_each(numberStr.begin(), numberStr.end(), [&](auto digit) {
		digitStack.push(atoi(&digit));
	});
	while (!digitStack.empty())
	{
		auto digit = digitStack.top();
		m_digits.push_back(digit);
		digitStack.pop();
	}
	m_size = m_digits.size();
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