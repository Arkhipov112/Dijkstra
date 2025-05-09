#include <stdexcept>

#include "graph.hpp"

void graph::add_edge(const std::string& from, const std::string& to, int dist) {
    if (dist < 0) {
        throw (std::invalid_argument("Distance cannot be negative"));
    }

    adjacency[from][to] = dist;
    adjacency[to][from] = dist;
}

bool graph::find_vertex(const std::string& vertex) const {
    return adjacency.count(vertex);
}

bool graph::find_edge(const std::string& from, const std::string& to) const {
    if ((!find_vertex(from)) || (!find_vertex(to))) {
        return false;
    }

    return adjacency.at(from).count(to);
}

int graph::get_dist(const std::string& from, const std::string& to) const {
    if (!find_edge(from, to)) {
        throw (std::invalid_argument("Edge does not exist"));
    }

    return adjacency.at(from).at(to);
}

std::vector<std::string> graph::get_vertexes() const {
    std::vector<std::string> res;

    for (const auto& v : adjacency) {
        res.push_back(v.first);
    }

    return res;
}

std::vector<std::string> graph::get_neighbors(const std::string& vertex) const {
    const auto& edges = adjacency.at(vertex);

    std::vector<std::string> res;

    for (const auto& e : edges) {
        res.push_back(e.first);
    }

    return res;
}