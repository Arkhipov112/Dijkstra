#include <sstream>
#include <stdexcept>

#include "parser.hpp"

namespace {
	const int PARSED_COUNT = 3;
}

graph parser::read(std::istream& in, const std::string& delims) {
    graph res;

    std::string line;
    while(std::getline(in, line)) {
        std::vector<std::string> temp = split(line, delims);

		if (temp.size() != PARSED_COUNT) {
			throw (std::invalid_argument("Does not match the type"));
		}

        res.add_edge(temp[0], temp[1], std::stoi(temp[2]));
    }

    return res;
}

void parser::write(std::ostream& out, const path& buffer) noexcept {
	out << "{ ";

	size_t len = buffer.first.size();
	for (int i = 0; i < len - 1; ++i) {
		out << buffer.first[i] << ", ";
	}

	out << buffer.first[len - 1] << " } - " << buffer.second;
}



std::vector<std::string> parser::split(const std::string& line, const std::string& delims) {
	std::vector<std::string> res;

	std::istringstream iss(line);
	std::string token;

	char c;
	while (iss.get(c)) {
		if (delims.find(c) != std::string::npos) {
			if (!token.empty()) {
				res.push_back(token);
				token.clear();
			}
		}

		else {
			token += c;
		}
	}

	if (!token.empty()) {
		res.push_back(token);
	}

	return res;
}