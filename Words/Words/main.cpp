#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
typedef map<char, size_t> Alphabet;
typedef pair<size_t, vector<string>> AcceptWords;

const int ARGUMENTS_COUNT = 2;


bool sort_func(const string &first, const string &second);
void ReadWords(ifstream &input, string &keyWord, vector<string> &gameWords);
Alphabet GetWordAlphabet(const string &word);
AcceptWords GetAcceptedWords(const Alphabet &alphabet, const vector<string> &words);

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		return 1;
	}

	ifstream input(argv[1]);
	string keyWord;
	vector<string> gameWords;

	ReadWords(input, keyWord, gameWords);
	auto alpthabet = GetWordAlphabet(keyWord);
	auto acceptWords = GetAcceptedWords(alpthabet, gameWords);

	cout << acceptWords.first << endl;
	std::sort(acceptWords.second.begin(), acceptWords.second.end(), sort_func);
	std::for_each(acceptWords.second.begin(), acceptWords.second.end(), [&](const string &word) {
		cout << word << endl;
	});

	return 0;
}

void ReadWords(ifstream &input, string &keyWord, vector<string> &gameWords)
{
	getline(input, keyWord);

	string gameWord;
	while (getline(input, gameWord))
	{
		gameWords.push_back(gameWord);
	}
}

Alphabet GetWordAlphabet(const string &word)
{
	Alphabet alphabet;
	std::for_each(word.begin(), word.end(), [&](const char &letter) {
		auto searchPair = alphabet.find(letter);
		if (searchPair == alphabet.end())
		{
			alphabet.insert(std::make_pair(letter, 1));
		}
		else
		{
			searchPair->second++;
		}
	});

	return alphabet;
}

AcceptWords GetAcceptedWords(const Alphabet &alphabet, const vector<string> &words)
{
	vector<string> acceptedWords;
	size_t points = 0;

	std::for_each(words.begin(), words.end(), [&](const string &word) {
		Alphabet testAlpthabet = alphabet;
		bool isAccept = true;

		for (size_t i = 0; i < word.size(); i++)
		{
			auto wordPair = testAlpthabet.find(word[i]);
			if (wordPair == testAlpthabet.end() || wordPair->second == 0)
			{
				isAccept = false;
				break;
			}
			wordPair->second--;
		}

		if (isAccept)
		{
			acceptedWords.push_back(word);
			points += word.length();
		}
	});

	return std::make_pair(points, acceptedWords);
}

bool sort_func(const string &first, const string &second)
{
	if (first.length() != second.length())
	{
		return (first.length() > second.length());
	}

	return (first < second);
}