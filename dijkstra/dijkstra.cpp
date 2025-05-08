#include <algorithm>
#include <limits>
#include <stdexcept>

#include "dijkstra.hpp"

Path Dijkstra::find(const Graph& graph, const std::string& start, const std::string& end) {
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

    std::vector<std::string> path;
    if (distances[end] == std::numeric_limits<int>::max()) {
        return std::make_pair(path, -1);
    }

    std::string current = end;
    while (current != start) {
        path.push_back(current);
        current = predecessors[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return std::make_pair(path, distances[end]);
}