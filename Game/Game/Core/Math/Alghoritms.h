#pragma once
#include "Basical_Type.h"

class Graph {
private:
	int numVertices;

	std::vector<std::vector<int>> adjLists;
	std::vector<bool> visited;

public:
	void AddEdge(int Src, int Dest);
	unsigned int GetAdjListSize();

	void DFS(int StartVertex, std::vector<int>* Output);
	void BFS(int StartVertex, std::vector<int>* Output);

	Graph(unsigned int size = 0);
};