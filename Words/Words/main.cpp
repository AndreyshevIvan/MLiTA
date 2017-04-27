#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "PriorityQueue.h"

using namespace std;
typedef map<char, size_t> Alphabet;

const int ARGUMENTS_COUNT = 2;

void ReadWords(ifstream &input, string &keyWord, vector<string> &gameWords);
Alphabet GetWordAlphabet(const string &word);
PriorityQueue GetAcceptedWords(const Alphabet &alphabet, const vector<string> &allWords, size_t &points);

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		return 1;
	}

	ifstream input(argv[1]);
	string keyWord;
	vector<string> gameWords;
	size_t points;

	ReadWords(input, keyWord, gameWords);

	auto alpthabet = GetWordAlphabet(keyWord);
	auto acceptWords = GetAcceptedWords(alpthabet, gameWords, points);

	cout << points << endl;
	while (!acceptWords.empty())
	{
		cout << acceptWords.top() << endl;
		acceptWords.pop();
	}

	return 0;
}

void ReadWords(ifstream &input, string &keyWord, vector<string> &gameWords)
{
	string gameWord;
	getline(input, keyWord);
	while (getline(input, gameWord))
	{
		gameWords.push_back(gameWord);
	}
}

Alphabet GetWordAlphabet(const string &word)
{
	Alphabet alphabet;
	for (const auto &letter : word)
	{
		auto searchPair = alphabet.find(letter);
		if (searchPair == alphabet.end())
		{
			alphabet.insert(std::make_pair(letter, 1));
			continue;
		}

		searchPair->second++;
	}

	return alphabet;
}

PriorityQueue GetAcceptedWords(const Alphabet &alphabet, const vector<string> &allWords, size_t &points)
{
	PriorityQueue acceptedWords;
	points = 0;

	for (const auto &word : allWords)
	{
		Alphabet testAlpthabet = alphabet;

		for (size_t i = 0; i < word.size(); i++)
		{
			auto wordPair = testAlpthabet.find(word[i]);
			if (wordPair == testAlpthabet.end() || wordPair->second == 0)
			{
				break;
			}
			wordPair->second--;
			if (i == word.size() - 1)
			{
				acceptedWords.push(word);
				points += word.length();
			}
		}
	}

	return acceptedWords;
}