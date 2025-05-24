#include "undirected_graph.hpp"

#include <stdexcept>

void UndirectedGraph::addEdge(const Vertex& v_1, const Vertex& v_2, int weight) {
    if (weight < 0) {
        throw (std::invalid_argument("Weight cannot be negative"));
    }

    adjacency[v_1][v_2] = weight;
    adjacency[v_2][v_1] = weight;
}

bool UndirectedGraph::findVertex(const Vertex& v) const {
    return adjacency.count(v);
}

bool UndirectedGraph::findEdge(const Vertex& v_1, const Vertex& v_2) const {
    if (!findVertex(v_1) || !findVertex(v_2)) {
        return false;
    }

    return adjacency.at(v_1).count(v_2);
}

int UndirectedGraph::getWeight(const Vertex& v_1, const Vertex& v_2) const {
    if (!findEdge(v_1, v_2)) {
        throw (std::invalid_argument("Edge does not exist"));
    }

    return adjacency.at(v_1).at(v_2);
}

std::vector<Vertex> UndirectedGraph::getVertices() const {
    std::vector<Vertex> vertices;

    for (const auto& v : adjacency) {
        vertices.push_back(v.first);
    }

    return vertices;
}

std::vector<Vertex> UndirectedGraph::getNeighbors(const Vertex& v) const {
    if (!findVertex(v)) {
        throw (std::invalid_argument("Vertex does not exist"));
    }

    std::vector<Vertex> neighbors;

    const auto& edges = adjacency.at(v);
    for (const auto& e : edges) {
        neighbors.push_back(e.first);
    }

    return neighbors;
}