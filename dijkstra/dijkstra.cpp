#include <algorithm>
#include <limits>
#include <stdexcept>

#include "dijkstra.hpp"

// Graph

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

// Dijkstra

Way Dijkstra::find(const Graph& graph, const std::string& start, const std::string& end) {
    if (!graph.findVertex(start) || !graph.findVertex(end)) {
        throw (std::invalid_argument("Start or end vertex does not exist"));
    }

    std::map<std::string, int> distances;
    std::map<std::string, bool> visited;
    std::map<std::string, std::string> predecessors;

    for (const auto& vertex : graph.getVertex()) {
        distances[vertex] = std::numeric_limits<int>::max();
        visited[vertex] = false;
    }

    distances[start] = 0;

    size_t count_vertex = graph.getVertex().size();
    for (size_t i = 0; i < count_vertex; ++i) {
        std::string current;
        int min_distance = std::numeric_limits<int>::max();

        for (const auto& vertex : graph.getVertex()) {
            if (!visited[vertex] && (distances[vertex] < min_distance)) {
                min_distance = distances[vertex];
                current = vertex;
            }
        }

        if (min_distance == std::numeric_limits<int>::max()) {
            break;
        }

        if (current == end) {
            break;
        }

        visited[current] = true;

        for (const auto& neighbor : graph.getNeighbors(current)) {
            int new_distance = distances[current] + graph.getDistance(current, neighbor);
            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                predecessors[neighbor] = current;
            }
        }
    }

    std::vector<std::string> way;
    if (distances[end] == std::numeric_limits<int>::max()) {
        return std::make_pair(way, -1);
    }

    std::string current = end;
    while (current != start) {
        way.push_back(current);
        current = predecessors[current];
    }
    way.push_back(start);
    std::reverse(way.begin(), way.end());

    return std::make_pair(way, distances[end]);
}