#pragma once

#include "../path/path.hpp"
#include "../undirected_graph/undirected_graph.hpp"
#include "../dijkstra/dijkstra.hpp"

#include <iostream>
#include <string>
#include <vector>

class Parser final {
public:
	Parser() = delete;
    static UndirectedGraph read(std::istream& in, const std::string& delimeters);
	static void write(std::ostream& out, const Path& buffer) noexcept;

private:
	static std::vector<std::string> split(const std::string& line, const std::string& delimeters);
};