#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

const int ARGUMENTS_COUNT = 3;

void ReadPeoples(std::ifstream& input, int& sellersCount, int& buyersCount);
void ReadPrices(std::ifstream& input, int sellers, int buyers, std::vector<int>& sellersPrice, std::vector<int>& buyersPrice);

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
		return 1;

	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);

	int sellers;
	int buyers;
	std::vector<int> sellersPrice;
	std::vector<int> buyersPrice;

	ReadPeoples(input, sellers, buyers);
	ReadPrices(input, sellers, buyers, sellersPrice, buyersPrice);

	std::vector<int> bestPrices;
	std::vector<int> sums;

	for (size_t currBuyer = 0; currBuyer != buyersPrice.size(); currBuyer++)
	{
		int currBuyerPrice = buyersPrice[currBuyer];
		int currBuyersCount = buyersPrice.size() - currBuyer;

		int currSellersCount = 0;
		for (size_t currSeller = 0; currSeller != sellersPrice.size(); currSeller++)
		{
			if (sellersPrice[currSeller] < currBuyerPrice)
			{
				currSellersCount++;
			}
		}

		int operationsCount = (currSellersCount < currBuyersCount) ? currSellersCount : currBuyersCount;

		bestPrices.push_back(currBuyerPrice);
		sums.push_back(operationsCount * currBuyerPrice);
	}

	int gain = 0;
	int bestPrice = 0;

	for (size_t i = 0; i != sums.size(); i++)
	{
		if (gain < sums[i])
		{
			gain = sums[i];
			bestPrice = buyersPrice[i];
		}
	}

	output << gain << " " << bestPrice;

	return 0;
}

void ReadPeoples(std::ifstream& input, int& sellersCount, int& buyersCount)
{
	input >> sellersCount;
	input >> buyersCount;
}

void ReadPrices(std::ifstream& input, int sellers, int buyers, std::vector<int>& sellersPrice, std::vector<int>& buyersPrice)
{
	int price;

	for (int i = 0; i < sellers; i++)
	{
		input >> price;
		sellersPrice.push_back(price);
	}

	for (int i = 0; i < buyers; i++)
	{
		input >> price;
		buyersPrice.push_back(price);
	}

	sort(sellersPrice.begin(), sellersPrice.end());
	sort(buyersPrice.begin(), buyersPrice.end());
}