#include "Alghoritms.h"

inline void Graph::AddEdge(int Src, int Dest) {
    Graph::adjLists[Src].push_back(Dest);
}

inline void Graph::DFS(int StartVertex, std::vector<int>* Output) {
    Graph::visited[StartVertex] = true;
    Output->push_back(StartVertex);

    for (size_t i = 0; i < Graph::adjLists[StartVertex].size(); i++)
    {
        if (!Graph::visited[Graph::adjLists[StartVertex][i]]) {
            Graph::DFS(Graph::adjLists[StartVertex][i], Output);
        }
    }
}

inline void Graph::BFS(int StartVertex, std::vector<int>* Output) {
    std::queue<int> q;
    visited[StartVertex] = true;
    q.push(StartVertex);

    while (!q.empty()) {
        int current = q.front();
        Output->push_back(current);
        q.pop();

        for (int i = 0; i < adjLists[current].size(); i++) {
            if (!visited[adjLists[current][i]]) {
                visited[adjLists[current][i]] = true;
                q.push(adjLists[current][i]);
            }
        }
    }
}

inline Graph::Graph(unsigned int size) {
    Graph::adjLists.resize(size);
    Graph::visited.resize(size);
}

inline unsigned int Graph::GetAdjListSize() {
    return Graph::adjLists.size();
}