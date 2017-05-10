#pragma once
#pragma once
#include <stdexcept>
#include <string>

class CException : public std::invalid_argument
{
public:
	CException(const std::string &message)
		: std::invalid_argument(message)
	{
	}
};