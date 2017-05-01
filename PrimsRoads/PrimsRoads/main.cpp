#include <set>

#include "ReadPrint.h"
#include "Structs.h"

void EnterProcess(const NodesMap &nodesMap, RoadsVect &ways, size_t &weightSum);
Road* GetBestRoad(const NodesSet &treeNodes);

int main()
{
	auto grapthNodesMap = ReadInput();
	
	if (grapthNodesMap.empty())
	{
		return 1;
	}

	std::vector<Road> roads;
	size_t weightSum = 0;

	EnterProcess(grapthNodesMap, roads, weightSum);
	SortRoads(roads);
	PrintRoads(roads, weightSum);

	return 0;
}

void EnterProcess(const NodesMap &nodesMap, RoadsVect &roads, size_t &weightSum)
{
	NodesSet treeNodes;
	auto grapthNodes = AsSet(nodesMap);
	auto startNode = *grapthNodes.begin();
	grapthNodes.erase(startNode);
	treeNodes.insert(startNode);

	while (!grapthNodes.empty())
	{
		auto bestRoad = GetBestRoad(treeNodes);

		if (!bestRoad)
		{
			break;
		}

		roads.push_back(*bestRoad);
		grapthNodes.erase(nodesMap.find(bestRoad->dstKey)->second);
		treeNodes.insert(nodesMap.find(bestRoad->dstKey)->second);
		weightSum += bestRoad->weight;
	}
}

Road* GetBestRoad(const NodesSet &treeNodes)
{
	Road* bestRoad = nullptr;

	auto set_new_best = [&](size_t src, size_t dst, size_t weight) {
		if (!bestRoad || bestRoad->weight > weight)
		{
			bestRoad = new Road(src, dst, weight);
		}
	};

	for (auto &nodeFromTree : treeNodes)
	{
		for (auto neighbourhoodRecord : nodeFromTree->neighbourhoods)
		{
			auto neighbourhood = neighbourhoodRecord.first;
			
			if (treeNodes.find(neighbourhood) == treeNodes.end())
			{
				auto weight = neighbourhoodRecord.second;
				set_new_best(nodeFromTree->key, neighbourhood->key, weight);
			}
		}
	}

	return bestRoad;
}