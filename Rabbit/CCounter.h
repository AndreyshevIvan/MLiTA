#pragma once
#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<unsigned short> Digits;

struct CCounter
{
public:
	void Set(size_t count)
	{
		if (count == 0)
		{
			m_digits = { 0 };
			return;
		}

		m_digits.clear();
		while (count > 0)
		{
			m_digits.push_back(count % 10);
			count /= 10;
		}
	}
	void Set(const CCounter &anotherCounter)
	{
		m_digits.clear();
		auto anotherDigits = anotherCounter.GetDigits();
		for (auto digit : anotherDigits)
		{
			m_digits.push_back(digit);
		}
	}
	void Add(const CCounter &counter)
	{
		auto get_digit = [](const Digits &digits, size_t pos) {
			return (pos < digits.size()) ? digits[pos] : 0;
		};

		Digits otherDigits = counter.GetDigits();
		size_t length = std::max(otherDigits.size(), m_digits.size());
		Digits newDigits;
		unsigned short toNext = 0;

		for (size_t i = 0; i < length; i++)
		{
			auto sum = get_digit(m_digits, i) + get_digit(otherDigits, i);
			auto toAdd = sum % 10;
			newDigits.push_back((toAdd + toNext) % 10);
			toNext = (toAdd + toNext) / 10 + ((sum < 10) ? 0 : 1);
		}

		if (toNext != 0)
		{
			newDigits.push_back(toNext);
		}

		m_digits = newDigits;
	}

	Digits GetDigits() const
	{
		return m_digits;
	}

	std::string ToString() const
	{
		std::string result;
		for (auto digit : m_digits)
		{
			result = std::to_string(digit) + result;
		}
		return result;
	}

private:
	Digits m_digits = { 0 };
};