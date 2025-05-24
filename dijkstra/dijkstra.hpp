#pragma once

#include "../vertex/vertex.hpp"
#include "../undirected_graph/undirected_graph.hpp"

#include <string>
#include <vector>

struct Path final {
    std::vector<Vertex> path;
    int weight;
};

class Dijkstra final {
public:
    Dijkstra() = delete;
    static Path findPath(const UndirectedGraph& ug, const Vertex& start, const Vertex& end);
};