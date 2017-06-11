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
		for (auto pos = digits.size() - 1; pos != 0; pos--)
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
	if (left.GetLength() != right.GetLength())
	{
		return left.GetLength() < right.GetLength();
	}

	auto leftDigits = left.GetDigits();
	auto rightDigits = right.GetDigits();

	for (int digitNum = left.GetLength() - 1; digitNum >= 0;)
	{
		if (leftDigits[digitNum] < rightDigits[digitNum])
		{
			return true;
		}
		else if (leftDigits[digitNum] > rightDigits[digitNum])
		{
			return false;
		}
		digitNum--;
	}
	return false;
}

bool operator ==(const CBigNumber &left, const CBigNumber &right)
{
	if (left.GetLength() != right.GetLength())
	{
		return false;
	}

	size_t digitNum = 0;
	auto leftDigits = left.GetDigits();
	auto rightDigits = right.GetDigits();

	while (digitNum != left.GetLength())
	{
		if (leftDigits[digitNum] != rightDigits[digitNum])
		{
			return false;
		}
		digitNum++;
	}

	return true;
}

CBigNumber operator -(const CBigNumber& left, const CBigNumber &right)
{
	if (left < right)
	{
		throw std::exception(LEFT_LESS);
	}

	auto leftDigits = left.GetDigits();
	auto rightDigits = right.GetDigits();
	size_t calcPos = 0;

	for (; calcPos < right.GetLength(); calcPos++)
	{
		if (leftDigits[calcPos] < rightDigits[calcPos])
		{
			TakeTen(leftDigits, calcPos);
		}
		leftDigits[calcPos] -= rightDigits[calcPos];
	}

	ClearZeroes(leftDigits);

	return leftDigits;
}