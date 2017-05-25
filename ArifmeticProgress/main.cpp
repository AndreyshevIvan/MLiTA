#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	std::string line;
	getline(input, line);

	size_t testCount = atoi(line.c_str());

	for (size_t i = 0; i < testCount; i++)
	{
		getline(input, line);
		std::stringstream stream(line);
		size_t numbersCount;
		stream >> numbersCount;

		if (numbersCount == 1 || numbersCount == 2)
		{
			getline(input, line);
			output << "Yes\n";
			continue;
		}

		getline(input, line);
		std::stringstream streamSecond(line);
		std::multiset<int> numbers;

		for (size_t j = 1; j <= numbersCount; j++)
		{
			int element;
			streamSecond >> element;
			numbers.insert(element);
		}

		auto next = numbers.begin();
		next++;
		auto k = *next - *numbers.begin();
		for (auto it = numbers.begin(); it != numbers.end(); it++)
		{
			int testK = *next - *it;
			if (testK != k)
			{
				output << "No\n";
				break;
			}
			next++;
			if (next == numbers.end())
			{
				output << "Yes\n";
				break;
			}
		}
	}

	return 0;
}