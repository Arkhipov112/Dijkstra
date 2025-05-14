#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../graph/graph.hpp"

class parser final {
public:
	parser() = delete;
    static graph read(std::istream& in, const std::string& delims);
	static void write(std::ostream& out, const std::string& buffer);

private:
	static std::vector<std::string> split(const std::string& line, const std::string& delims);
};