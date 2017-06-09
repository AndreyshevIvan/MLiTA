#include "BigNumber.h"

namespace
{
	const char* LEFT_LESS = "BigNumber(-): left less than right.";
	const char* OUT_OF_TAKE = "TakeTen: take out of vector.";

	void TakeTen(Digits &digits, size_t recipientPos);
	void ClearZeroes(Digits &digits);

	void TakeTen(Digits &digits, size_t recipientPos)
	{
		size_t takePos = recipientPos + 1;
		while (digits[takePos] == 0)
		{
			takePos++;
			if (takePos >= digits.size())
			{
				throw std::exception(OUT_OF_TAKE);
			}
		}

		digits[takePos] -= 1;
		while (takePos > recipientPos)
		{
			takePos--;
			digits[takePos] += 9;
		}
		digits[recipientPos]++;
	}

	void ClearZeroes(Digits &digits)
	{
		for (auto pos = digits.size() - 1; pos != 1; pos--)
		{
			if (digits[pos] != 0)
			{
				return;
			}
			digits.pop_back();
		}
	}
}

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

	for (auto digitNum = left.Length() - 1; digitNum >= 0;)
	{
		if (leftDigits[digitNum] < rightDigits[digitNum])
		{
			return true;
		}
		digitNum--;
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

CBigNumber operator -(const CBigNumber& left, const CBigNumber &right)
{
	if (left < right)
	{
		throw std::exception(LEFT_LESS);
	}
	if (left == right)
	{
		return CBigNumber(0);
	}

	auto leftDigits = left.GetDigits();
	auto rightDigits = right.GetDigits();
	Digits newDigits;
	size_t calcPos = 0;

	for (; calcPos < right.Length(); calcPos++)
	{
		if (leftDigits[calcPos] < rightDigits[calcPos])
		{
			TakeTen(leftDigits, calcPos);
		}
		newDigits.push_back(leftDigits[calcPos] - rightDigits[calcPos]);
	}

	for (; calcPos < left.Length(); calcPos++)
	{
		newDigits.push_back(leftDigits[calcPos]);
	}

	ClearZeroes(newDigits);

	return CBigNumber(newDigits);
}