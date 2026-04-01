// PrimsAlgo.cpp
#include "prim.h"
#include <iostream>
#include <fstream>
#include <queue>

void primsAlgorithm(const Graph& graph, int start, int numVerts) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minHeap;

    std::vector<bool> inMST(numVerts, false);
    std::vector<int>  key(numVerts, INT_MAX);
    std::vector<int>  parent(numVerts, -1);

    key[start] = 0;
    minHeap.push({ 0, start });

    int totalWeight = 0;
    std::vector<std::pair<int, int>> mstEdges;

    while (!minHeap.empty()) {
        auto [weight, u] = minHeap.top();
        minHeap.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        totalWeight += weight;

        if (parent[u] != -1)
            mstEdges.push_back({ parent[u], u });

        for (auto [edgeWeight, v] : graph[u]) {
            if (!inMST[v] && edgeWeight < key[v]) {
                key[v] = edgeWeight;
                parent[v] = u;
                minHeap.push({ edgeWeight, v });
            }
        }
    }

    std::cout << "Minimum Spanning Tree edges:\n";
    for (auto [u, v] : mstEdges)
        std::cout << "  " << u << " -- " << v
        << "  (weight: " << key[v] << ")\n";

    std::cout << "Total MST weight: " << totalWeight << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Error: cannot open file '" << argv[1] << "'\n";
        return 1;
    }

    int startVertex, numEdges;
    inFile >> startVertex >> numEdges;

    std::vector<int> edgeU(numEdges), edgeV(numEdges);
    for (int i = 0; i < numEdges; ++i)
        inFile >> edgeU[i] >> edgeV[i];

    std::vector<int> edgeW(numEdges);
    for (int i = 0; i < numEdges; ++i)
        inFile >> edgeW[i];

    int numVerts = 0;
    for (int i = 0; i < numEdges; ++i)
        numVerts = std::max(numVerts, std::max(edgeU[i], edgeV[i]) + 1);
    numVerts = std::max(numVerts, startVertex + 1);

    Graph graph(numVerts);
    for (int i = 0; i < numEdges; ++i) {
        graph[edgeU[i]].push_back({ edgeW[i], edgeV[i] });
        graph[edgeV[i]].push_back({ edgeW[i], edgeU[i] });
    }

    std::cout << "Graph has " << numVerts << " vertices and "
        << numEdges << " edges.\n";
    std::cout << "Running Prim's Algorithm from vertex " << startVertex << ":\n\n";

    primsAlgorithm(graph, startVertex, numVerts);

    return 0;
}