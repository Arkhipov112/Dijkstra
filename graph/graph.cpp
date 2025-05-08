#include <stdexcept>

#include "graph.hpp"

void Graph::addEdge(const std::string& from, const std::string& to, int distance) {
    if (distance < 0) {
        throw (std::invalid_argument("The distance cannot be negative"));
    }

    adjacency[from][to] = distance;
}

bool Graph::findVertex(const std::string& vertex) const noexcept {
    return adjacency.count(vertex);
}

bool Graph::findEdge(const std::string& from, const std::string& to) const noexcept {
    if (!findVertex(from) || !findVertex(to)) {
        return false;
    }

    return adjacency.at(from).count(to);
}

int Graph::getDistance(const std::string& from, const std::string& to) const {
    if (!findEdge(from, to)) {
        throw (std::out_of_range("Edge does not exist"));
    }

    return adjacency.at(from).at(to);
}

std::vector<std::string> Graph::getVertex() const noexcept {
    std::vector<std::string> result;

    for (const auto& vertex : adjacency) {
        result.push_back(vertex.first);
    }

    return result;
}

std::vector<std::string> Graph::getNeighbors(const std::string& vertex) const {
    const auto& edges = adjacency.at(vertex);

    std::vector<std::string> result;

    for (const auto& edge : edges) {
        result.push_back(edge.first);
    }

    return result;
}