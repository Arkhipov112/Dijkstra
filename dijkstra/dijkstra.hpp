#pragma once
#include <map>
#include <string>
#include <vector>

#include "../graph/graph.hpp"

typedef std::pair<std::vector<std::string>, int> Way;

class Dijkstra final {
public:
    static Way find(const Graph& graph, const std::string& start, const std::string& end);
};