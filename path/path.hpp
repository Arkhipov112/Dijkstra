#pragma once

#include "../vertex/vertex.hpp"

#include <vector>

struct Path final {
    std::vector<Vertex> path;
    int weight;
};