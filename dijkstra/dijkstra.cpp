#include "dijkstra.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace {
    const int INF = std::numeric_limits<int>::max();
}

Path Dijkstra::findPath(const UndirectedGraph& ug, const Vertex& start, const Vertex& end) {
    if (!ug.findVertex(start) || !ug.findVertex(end)) {
        throw (std::invalid_argument("Start or end vertex does not exist"));
    }

    std::map<Vertex, int> dists;
    std::map<Vertex, bool> visited;
    std::map<Vertex, Vertex> preds;

    for (const auto& v : ug.getVertices()) {
        dists[v] = INF;
        visited[v] = false;
    }

    dists[start] = 0;

    for (size_t i = 0; i < ug.getVertices().size(); ++i) {
        Vertex nearest;
        int min_dist = INF;

        for (const auto& v : ug.getVertices()) {
            if (!visited[v] && (dists[v] < min_dist)) {
                min_dist = dists[v];
                nearest = v;
            }
        }

        visited[nearest] = true;

        for (const auto& n : ug.getNeighbors(nearest)) {
            int new_dist = dists[nearest] + ug.getWeight(nearest, n);
            if (new_dist < dists[n]) {
                dists[n] = new_dist;
                preds[n] = nearest;
            }
        }
    }

    Path p;

    Vertex current = end;
    while (current != start) {
        p.path.push_back(current);
        current = preds[current];
    }
    p.path.push_back(start);
    std::reverse(p.path.begin(), p.path.end());

    p.weight = dists[end];

    return p;
}