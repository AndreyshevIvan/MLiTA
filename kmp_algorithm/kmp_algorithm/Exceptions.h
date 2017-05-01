#pragma once
#include <stdexcept>
#include <string>

class CInputException : public std::invalid_argument
{
public:
	CInputException(const std::string &message)
		: std::invalid_argument(message)
	{
	}
};