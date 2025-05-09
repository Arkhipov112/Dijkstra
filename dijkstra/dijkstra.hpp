#pragma once
#include <map>
#include <string>
#include <vector>

#include "../graph/graph.hpp"

typedef std::pair<std::vector<std::string>, int> path;

class dijkstra final {
public:
    static path find_path(const graph& g, const std::string& start, const std::string& end);
};