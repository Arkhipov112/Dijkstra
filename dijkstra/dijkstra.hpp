#pragma once
#include <map>
#include <string>
#include <vector>

#include "../graph/graph.hpp"

typedef std::pair<std::vector<std::string>, int> Path;

class Dijkstra final {
public:
    static Path find(const Graph& graph, const std::string& start, const std::string& end);
};