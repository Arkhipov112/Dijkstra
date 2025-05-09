#include <stdexcept>

#include "parser.hpp"

namespace {
	const int PARSED_COUNT = 3;
}

graph parser::read(std::istream& in, const std::string& delims) {
    graph res;

    std::string line;
    while(std::getline(in, line)) {
        std::vector<std::string> temp = parse(split(trim(line), delims));

		if (temp.size() != PARSED_COUNT) {
			throw (std::invalid_argument("Does not match the type"));
		}

        res.add_edge(temp[0], temp[1], std::stoi(temp[2]));
    }

    return res;
}

std::string parser::trim(const std::string& line) noexcept {
	std::string res;

	std::string whitespace = " \t";

	size_t first = line.find_first_not_of(whitespace);
	if (first == std::string::npos) {
		return res;
	}

	size_t last = line.find_last_not_of(whitespace);

	res = line.substr(first, (last - first) + 1);

	return res;
}

std::string parser::split(const std::string& line, const std::string& delims) noexcept {
	std::string res;

	bool need_space = false;
	for (char c : line) {
		if (delims.find(c) != std::string::npos) {
			need_space = true;
		}

		else {
			if (need_space) {
				res += ' ';
				need_space = false;
			}

			res += c;
		}
	}

	return res;
}

std::vector<std::string> parser::parse(const std::string& line) noexcept {
	std::vector<std::string> res;

	size_t first = 0;
	size_t last = line.find(' ');

	while (last != std::string::npos) {
		res.push_back(line.substr(first, last - first));
		first = last + 1;
		last = line.find(' ', first);
	}
	res.push_back(line.substr(first));

	return res;
}