#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

typedef std::multiset<std::pair<int, size_t>> Set;

namespace
{
}

Set Read(std::ifstream &input);
int GetDelta(int first, int second);
void Write(std::ofstream &output, int delta, size_t minIndex, size_t maxIndex);

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	auto numbers = Read(input);

	auto prev = numbers.begin();
	auto curr = numbers.begin()++;
	curr++;
	auto next = numbers.begin();
	next++;
	next++;

	int delta = INT_MAX;
	size_t maxIndex = 0;
	size_t minIndex = 0;

	do 
	{
		int newDelta = curr->first - prev->first;
		size_t newMinIndex = std::min(prev->second, curr->second);
		size_t newMaxIndex = std::max(prev->second, curr->second);

		if (newDelta < delta)
		{
			delta = newDelta;
			minIndex = newMinIndex;
			maxIndex = newMaxIndex;
		}
		else if (newDelta == delta && newMinIndex < minIndex)
		{
			delta = newDelta;
			minIndex = newMinIndex;
			maxIndex = newMaxIndex;
		}

		newDelta = next->first - curr->first;
		newMinIndex = std::min(next->second, curr->second);
		newMaxIndex = std::max(next->second, curr->second);

		if (newDelta < delta)
		{
			delta = newDelta;
			minIndex = newMinIndex;
			maxIndex = newMaxIndex;
		}
		else if (newDelta == delta && newMinIndex < minIndex)
		{
			delta = newDelta;
			minIndex = newMinIndex;
			maxIndex = newMaxIndex;
		}

		prev++;
		curr++;
		next++;
	} while (next != numbers.end());

	Write(output, delta, minIndex, maxIndex);

	return 0;
}

Set Read(std::ifstream &input)
{
	size_t numsCount;
	input >> numsCount;
	Set result;

	for (size_t i = 0; i < numsCount; i++)
	{
		int number;
		input >> number;
		result.insert(std::make_pair(number, i + 1));
	}

	return result;
}

int GetDelta(int first, int second)
{
	return std::max(first, second) - std::min(first, second);
}

void Write(std::ofstream &output, int delta, size_t minIndex, size_t maxIndex)
{
	output << delta << std::endl;
	output << minIndex << ' ' << maxIndex << std::endl;
}