#include <algorithm>
#include <limits>
#include <stdexcept>

#include "dijkstra.hpp"

path dijkstra::find_path(const graph& g, const std::string& start, const std::string& end) {
    if ((!g.find_vertex(start)) || (!g.find_vertex(end))) {
        throw (std::invalid_argument("Start or end vertex does not exist"));
    }

    std::map<std::string, int> dists;
    std::map<std::string, bool> visited;
    std::map<std::string, std::string> preds;

    for (const auto& v : g.get_vertexes()) {
        dists[v] = std::numeric_limits<int>::max();
        visited[v] = false;
    }

    dists[start] = 0;

    for (size_t i = 0; i < g.get_vertexes().size(); ++i) {
        std::string current;
        int min_dist = std::numeric_limits<int>::max();

        for (const auto& v : g.get_vertexes()) {
            if (!visited[v] && (dists[v] < min_dist)) {
                min_dist = dists[v];
                current = v;
            }
        }

        if (min_dist == std::numeric_limits<int>::max()) {
            break;
        }

        if (current == end) {
            break;
        }

        visited[current] = true;

        for (const auto& n : g.get_neighbors(current)) {
            int new_dist = dists[current] + g.get_dist(current, n);
            if (new_dist < dists[n]) {
                dists[n] = new_dist;
                preds[n] = current;
            }
        }
    }

    std::vector<std::string> path;
    if (dists[end] == std::numeric_limits<int>::max()) {
        return std::make_pair(path, -1);
    }

    std::string current = end;
    while (current != start) {
        path.push_back(current);
        current = preds[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return std::make_pair(path, dists[end]);
}