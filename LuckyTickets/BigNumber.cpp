#include "BigNumber.h"

namespace
{
	const char* EMPTY_STR = "CBigNumber: create from empty string is not allowed.";
}

CBigNumber::CBigNumber(const std::string &numberStr)
{
	if (numberStr.empty())
	{
		throw std::exception(EMPTY_STR);
	}

	m_size = numberStr.length();
}