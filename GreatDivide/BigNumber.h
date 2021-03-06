#pragma once
#include <vector>
#include <string>

typedef std::vector<unsigned short> Digits;

class CBigNumber
{
public:
	CBigNumber();
	CBigNumber(const std::string &numberStr);
	CBigNumber(const CBigNumber &bigNumber);

	Digits GetDigits() const;
	size_t Length() const;
	std::string ToString() const;

private:
	Digits m_digits;
	size_t m_size;

};

bool operator ==(const CBigNumber &left, const CBigNumber &right);
bool operator <(const CBigNumber &left, const CBigNumber &right);
bool operator !=(const CBigNumber &left, const CBigNumber &right);

std::ostream &operator <<(std::ostream &stream, const CBigNumber &number);
