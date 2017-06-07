#include <string>
#include <algorithm>
#include <map>

#include "CCounter.h"

struct ValuesMap
{
	ValuesMap()
	{
		CCounter zero;
		CCounter one;
		zero.Set(0);
		one.Set(1);
		TryAdd(0, zero);
		TryAdd(1, one);
	}

	void TryAdd(size_t value, CCounter count)
	{
		auto record = valueMap.find(value);
		if (record == valueMap.end())
		{
			valueMap.insert(std::make_pair(value, count));
		}
	}

	bool Get(size_t value, CCounter &count)
	{
		auto record = valueMap.find(value);
		if (record == valueMap.end())
		{
			return false;
		}
		count = record->second;
		return true;
	}

	std::map<size_t, CCounter> valueMap;
};

CCounter func(ValuesMap &valuesMap, int ladderSize, int stepSize);

int main()
{
	try
	{
		std::ifstream input("input.txt");
		std::ofstream output("output.txt");

		size_t ladderSize = 0;
		size_t stepSize = 0;
		input >> ladderSize >> stepSize;

		ValuesMap valuesMap;
		auto count = func(valuesMap, ladderSize, stepSize);
		output << count.ToString() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

CCounter func(ValuesMap &valuesMap, int maxLadder, int stepSize)
{
	CCounter result;

	if (valuesMap.Get(maxLadder, result))
	{
		return result;
	}

	if (maxLadder < 0)
	{
		result.Set(0);
		return result;
	}

	result.Set((maxLadder - stepSize <= 0) ? 1 : 0);

	for (auto i = maxLadder - 1; i >= maxLadder - stepSize; i--)
	{
		auto newResult = func(valuesMap, i, stepSize);
		result.Add(newResult);
		valuesMap.TryAdd(i, newResult);
	}

	return result;
}