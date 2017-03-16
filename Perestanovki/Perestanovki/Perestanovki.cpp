#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void ReadInfo(ifstream& file, int& digitCount, int& permutations—ount);
void ReadNumbers(ifstream& file, vector<int>& permutation, int digitCount);

void WriteInfo(int digitCount, int permutations—ount, vector<int> const& permutation);
void WriteVector(vector<int> const& permutation);

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");

	int digitCount = 0;
	int permutations—ount = 0;
	vector<int> permutation;

	ReadInfo(input, digitCount, permutations—ount);
	ReadNumbers(input, permutation, digitCount);
		
	for (size_t j = permutation.size() - 1; j > 0; j--)
	{
		int startPos = 0;

		if (permutation[j] > permutation[j - 1])
		{
			startPos = j - 1;
			int startDigit = permutation[startPos];
			int toSwap = INT_MAX;
			int toSwapPos = j;

			for (size_t k = j; k < permutation.size(); k++)
			{
				if (permutation[k] > startDigit)
				{
					if (toSwap > permutation[k])
					{
						toSwap = permutation[k];
						toSwapPos = k;
					}
				}
			}

			if (toSwap != INT_MAX)
			{
				permutation[toSwapPos] = startDigit;
				permutation[startPos] = toSwap;

				vector<int> invertVect;

				for (size_t k = j; k < permutation.size(); k++)
				{
					invertVect.push_back(permutation[k]);
				}

				int pos = 0;
				for (size_t k = permutation.size() - 1; k >= j; k--)
				{
					permutation[k] = invertVect[pos];
					pos++;
				}

				WriteVector(permutation);
				j = permutation.size();

				permutations—ount--;
				if (permutations—ount == 0)
				{
					break;
				}
			}
		}

	}

	return 0;
}

void ReadInfo(ifstream& file, int& digitCount, int& permutations—ount)
{
	string str;
	getline(file, str);
	stringstream sstr(str);
	sstr >> digitCount;
	sstr >> permutations—ount;
}

void ReadNumbers(ifstream& file, vector<int>& permutation, int digitCount)
{
	for (int i = 0; i < digitCount; i++)
	{
		int digit = 0;
		file >> digit;
		permutation.push_back(digit);
	}
}

void WriteInfo(int digitCount, int permutations—ount, vector<int> const& permutation)
{
	cout << digitCount << "\n";
	cout << permutations—ount << "\n";

	for (size_t i = 0; i < permutation.size(); i++)
	{
		cout << permutation[i] << " ";
	}
	cout << "\n";
}

void WriteVector(vector<int> const& permutation)
{
	for (size_t i = 0; i < permutation.size(); i++)
	{
		cout << permutation[i];
	}
	cout << "\n";
}
