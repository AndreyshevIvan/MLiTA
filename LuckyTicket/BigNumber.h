#pragma once
#include <vector>
#include <string>

typedef std::vector<unsigned short> Digits;

class CBigNumber
{
public:
	CBigNumber(size_t number = 0);
	CBigNumber(const Digits &digits);
	CBigNumber(std::string numberStr);
	CBigNumber(const CBigNumber &bigNumber);

	void SmartIncrement(size_t position);

	Digits GetDigits() const;
	unsigned short GetDigit(size_t digitPosition) const;
	char GetDigitChar(size_t digitPosition) const;
	size_t GetLength() const;
	size_t GetDigitSum() const;

	void SetDigit(size_t digitPosition, unsigned short value);

	std::string ToString() const;
	std::pair<CBigNumber, CBigNumber> Split() const;

private:
	Digits m_digits;

};

bool operator ==(const CBigNumber &left, const CBigNumber &right);
bool operator <(const CBigNumber &left, const CBigNumber &right);

CBigNumber operator -(const CBigNumber& left, const CBigNumber &right);
