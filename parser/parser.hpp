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
	static std::string trim(const std::string& line) noexcept;
	static std::string split(const std::string& line, const std::string& delims) noexcept;
	static std::vector<std::string> parse(const std::string& line) noexcept;
};