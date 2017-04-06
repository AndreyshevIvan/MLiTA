#pragma once
#include "stdafx.h"

using namespace std;

struct Node
{
	size_t number = 0;
	set<size_t> needToPass;
};