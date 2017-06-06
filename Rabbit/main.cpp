#include <fstream>
#include <iostream>
#include <climits>

unsigned __int64 Calc(int iprev, int n, int k);

int main()
{
	std::ifstream input("input.txt");

	size_t ladderSize;
	size_t rabbitStep;
	input >> ladderSize >> rabbitStep;

	try
	{
		std::cout << Calc(0, ladderSize, rabbitStep) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
	}

	return 0;
}

unsigned __int64 Calc(int iprev, int n, int k)
{
	unsigned __int64 result = 0;

	for (int i = 1; i <= k; i++)
	{
		if ((iprev + i) < n)
		{
			unsigned __int64 newResult = Calc(iprev + i, n, k);;
			if (_UI64_MAX - result < newResult)
			{
				throw std::exception("overflow!");
			}
			result += newResult;
			
		}
		else if ((iprev + i) == n)
		{
			result++;
		}
	}

	//std::cout << result << std::endl;
	return result;
}