#pragma once

class Utils
{
public:

	static int Int(char symbol)
	{
		return int(symbol - '0');
	}
	static char Ch(int number)
	{
		return number + '0';
	}
};