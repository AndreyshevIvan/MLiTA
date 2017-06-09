#include "BigNumber.h"

bool operator <(const CBigNumber &left, const CBigNumber &right)
{
	if (left == right)
	{
		return false;
	}

	auto leftLen = left.Length();
	auto rightLen = right.Length();

	if (leftLen != rightLen)
	{
		return leftLen < rightLen;
	}

	auto leftDigits = left.GetDigits();
	auto rightDigits = right.GetDigits();

	for (auto digitNum = left.Length() - 1; digitNum > 0; digitNum--)
	{
		if (leftDigits[digitNum] < rightDigits[digitNum])
		{
			return true;
		}
	}

	return false;
}

bool operator ==(const CBigNumber &left, const CBigNumber &right)
{
	if (left.Length() != right.Length())
	{
		return false;
	}

	size_t digitNum = 0;
	auto leftDigits = left.GetDigits();
	auto rightDigits = right.GetDigits();

	while (digitNum != left.Length())
	{
		if (leftDigits[digitNum] != rightDigits[digitNum])
		{
			return false;
		}
		digitNum++;
	}

	return true;
}

bool operator !=(const CBigNumber &left, const CBigNumber &right)
{
	return !(left == right);
}

std::ostream &operator <<(std::ostream &stream, const CBigNumber &number)
{
	stream << number.ToString();
	return stream;
}