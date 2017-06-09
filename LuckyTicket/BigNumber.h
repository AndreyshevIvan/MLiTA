#pragma once
#include <vector>
#include <string>

typedef std::vector<unsigned short> Digits;

class CBigNumber
{
public:
	CBigNumber();
	CBigNumber::CBigNumber(size_t number);
	CBigNumber(const Digits &digits);
	CBigNumber(const std::string &numberStr);
	CBigNumber(const CBigNumber &bigNumber);

	Digits GetDigits() const;
	size_t Length() const;
	std::string ToString() const;

private:
	Digits m_digits;

};

bool operator ==(const CBigNumber &left, const CBigNumber &right);
bool operator <(const CBigNumber &left, const CBigNumber &right);
bool operator !=(const CBigNumber &left, const CBigNumber &right);

CBigNumber operator -(const CBigNumber& left, const CBigNumber &right);

std::ostream &operator <<(std::ostream &stream, const CBigNumber &number);
