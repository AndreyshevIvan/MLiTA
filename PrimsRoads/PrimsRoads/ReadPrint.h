#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

#include "Structs.h"

namespace
{
	const std::string INPUT_FILE_NAME = "input.txt";
	const std::string OUTPUT_FILE_NAME = "output.txt";

	void GetMapInfo(std::ifstream &input, size_t &nodesCount, size_t &roadsCount)
	{
		std::string fileLine;
		getline(input, fileLine);
		std::stringstream stream(fileLine);

		stream >> nodesCount;
		stream >> roadsCount;
	}

	NodesMap GetNodesFromInfo(size_t nodesCount)
	{
		NodesMap result;

		while (nodesCount > 0)
		{
			auto node = new Node(nodesCount);
			result.insert(std::make_pair(nodesCount, node));
			nodesCount--;
		}

		return result;
	}

	void LinkNodes(std::ifstream &input, NodesMap &nodesMap)
	{
		std::string fileLine;
		size_t firstKey;
		size_t secondKey;
		size_t weight;

		while (getline(input, fileLine))
		{
			std::stringstream stream(fileLine);
			stream >> firstKey;
			stream >> secondKey;
			stream >> weight;

			auto firstNode = nodesMap.find(firstKey)->second;
			auto secondNode = nodesMap.find(secondKey)->second;

			firstNode->neighbourhoods.insert(std::make_pair(secondNode, weight));
			secondNode->neighbourhoods.insert(std::make_pair(firstNode, weight));
		}
	}
}

NodesMap ReadInput()
{
	std::ifstream input(INPUT_FILE_NAME);

	size_t nodesCount;
	size_t roadsCount;

	GetMapInfo(input, nodesCount, roadsCount);
	NodesMap nodesMap = GetNodesFromInfo(nodesCount);
	LinkNodes(input, nodesMap);

	return nodesMap;
}

NodesSet AsSet(const NodesMap &nodesMap)
{
	NodesSet nodesSet;

	for (auto &mapRecord : nodesMap)
	{
		nodesSet.insert(mapRecord.second);
	}

	return nodesSet;
}

void PrintRoads(const RoadsVect &roadsToPrint, size_t weightSum)
{
	std::ofstream output(OUTPUT_FILE_NAME);

	output << weightSum << std::endl;

	for (auto &road : roadsToPrint)
	{
		auto firstKey = road.srcKey;
		auto secondKey = road.dstKey;

		if (firstKey < secondKey)
		{
			output << firstKey << " " << secondKey;
		}
		else
		{
			output << secondKey << " " << firstKey;
		}

		output << std::endl;
	}
}

void SortRoads(RoadsVect &roads)
{
	for (auto &road : roads)
	{
		if (road.srcKey > road.dstKey)
		{
			std::swap(road.srcKey, road.dstKey);
		}
	}

	auto sort_func = [&](const Road &first, const Road &second) {
		auto firstKey = first.srcKey;
		auto secondKey = second.srcKey;

		if (firstKey == secondKey)
		{
			return first.dstKey < second.dstKey;
		}

		return firstKey < secondKey;
	};

	std::sort(roads.begin(), roads.end(), sort_func);
}