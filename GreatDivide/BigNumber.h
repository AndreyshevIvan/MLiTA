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

private:
	Digits m_digits;
	size_t m_size;

};