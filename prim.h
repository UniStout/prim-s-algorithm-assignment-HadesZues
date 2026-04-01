//Please put header information in this file.
#pragma once

#include <vector>
#include <climits>

// Type aliases shared across files
using Edge = std::pair<int, int>;
using Graph = std::vector<std::vector<Edge>>;

/**
 * Prim's Algorithm - Minimum Spanning Tree
 *
 * @param graph     Adjacency list of the graph
 * @param start     Starting vertex
 * @param numVerts  Total number of vertices
 */
void primsAlgorithm(const Graph& graph, int start, int numVerts);