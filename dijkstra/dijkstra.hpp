#pragma once

#include "../path/path.hpp"
#include "../vertex/vertex.hpp"
#include "../undirected_graph/undirected_graph.hpp"

class Dijkstra final {
public:
    Dijkstra() = delete;
    static Path findPath(const UndirectedGraph& ug, const Vertex& start, const Vertex& end);
};