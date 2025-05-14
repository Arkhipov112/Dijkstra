#include <algorithm>
#include <limits>
#include <stdexcept>

#include "dijkstra.hpp"

namespace {
    const int INF = std::numeric_limits<int>::max();
}

path dijkstra::find_path(const graph& g, const std::string& start, const std::string& end) {
    if ((!g.find_vertex(start)) || (!g.find_vertex(end))) {
        throw (std::invalid_argument("Start or end vertex does not exist"));
    }

    std::map<std::string, int> dists;
    std::map<std::string, bool> visited;
    std::map<std::string, std::string> preds;

    for (const auto& v : g.get_vertexes()) {
        dists[v] = INF;
        visited[v] = false;
    }

    dists[start] = 0;

    for (size_t i = 0; i < g.get_vertexes().size(); ++i) {
        std::string nearest;
        int min_dist = INF;

        for (const auto& v : g.get_vertexes()) {
            if (!visited[v] && (dists[v] < min_dist)) {
                min_dist = dists[v];
                nearest = v;
            }
        }

        visited[nearest] = true;

        for (const auto& n : g.get_neighbors(nearest)) {
            int new_dist = dists[nearest] + g.get_dist(nearest, n);
            if (new_dist < dists[n]) {
                dists[n] = new_dist;
                preds[n] = nearest;
            }
        }
    }

    std::vector<std::string> path;

    std::string current = end;
    while (current != start) {
        path.push_back(current);
        current = preds[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return std::make_pair(path, dists[end]);
}