#pragma once

#include "../vertex/vertex.hpp"

#include <map>
#include <vector>

class UndirectedGraph final {
public:
    void addEdge(const Vertex& v_1, const Vertex& v_2, int weight);
    bool findVertex(const Vertex& v) const;
    bool findEdge(const Vertex& v_1, const Vertex& v_2) const;
    int getWeight(const Vertex& v_1, const Vertex& v_2) const;
    std::vector<Vertex> getVertices() const;
    std::vector<Vertex> getNeighbors(const Vertex& v) const;
    
private:
    std::map<Vertex, std::map<Vertex, int>> adjacency;
};