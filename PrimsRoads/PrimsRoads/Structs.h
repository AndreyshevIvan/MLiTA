#pragma once
#include <vector>
#include <map>
#include <queue>

struct Node
{
	Node(size_t nodeKey)
		: key(nodeKey)
	{
	}

	size_t key;
	std::map<Node*, size_t> neighbourhoods;
};

struct Road
{
	Road(size_t src, size_t dst, size_t weight)
		: srcKey(src)
		, dstKey(dst)
		, weight(weight)
	{
	}
	size_t weight;
	size_t dstKey;
	size_t srcKey;
};

typedef std::map<size_t, Node*> NodesMap;
typedef std::set<Node*> NodesSet;
typedef std::vector<Road> RoadsVect;
