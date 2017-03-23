#include "stdafx.h"
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void WriteCode(stack<size_t> code, size_t codeSize);
void CreateNewCode(stack<size_t> &code, size_t size);

int main()
{
	std::string code;
	std::cin >> code;
	size_t size = code.length();

	size_t newCodesCount;
	std::cin >> newCodesCount;

	stack<size_t> codeStack;

	for (size_t i = 0; i < size; i++)
	{
		if (code[i] == '1')
		{
			codeStack.push(size - i - 1);
		}
	}

	for (size_t i = 0; i < newCodesCount; i++)
	{
		CreateNewCode(codeStack, size);
		WriteCode(codeStack, size);
	}

	return 0;
}

void WriteCode(stack<size_t> code, size_t codeSize)
{
	size_t firstOne = 0;
	vector<size_t> vec;

	while (!code.empty())
	{
		vec.push_back(codeSize - code.top() - 1);
		code.pop();
	}

	for (size_t i = 0; i < codeSize; i++)
	{
		if (!vec.empty() && i == vec.front())
		{
			cout << 1;
			vec.erase(vec.begin());
		}
		else
		{
			cout << 0;
		}
	}

	cout << "\n";
}

void CreateNewCode(stack<size_t> &code, size_t size)
{
	if (code.empty())
	{
		code.push(0);
	}
	else if (code.top() != 0)
	{
		code.push(0);
	}
	else if (code.top() == size - 1)
	{
		code.pop();
	}
	else
	{
		size_t codeTop = code.top();
		cout << "Code top: " << codeTop;

		code.pop();

		if (!code.empty() && code.top() == codeTop + 1)
		{
			CreateNewCode(code, size);
		}
		else
		{
			code.push(codeTop + 1);
		}
	}
}