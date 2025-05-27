#include "parser.hpp"

#include <sstream>
#include <stdexcept>

namespace {
	const int PARSED_COUNT = 3;
}

UndirectedGraph Parser::read(std::istream& in, const std::string& delimeters) {
    UndirectedGraph ug;

    std::string line;
    while(std::getline(in, line)) {
        std::vector<std::string> temp = split(line, " " + delimeters);

		try {
			if (temp.size() == PARSED_COUNT) {
        		ug.addEdge(Vertex(temp[0]), Vertex(temp[1]), std::stoi(temp[2]));
			}
		}

		catch (const std::exception& ex) {
			continue;
		}
	}

    return ug;
}

void Parser::write(std::ostream& out, const Path& buffer) noexcept {
	out << "{ ";

	size_t len = buffer.path.size();
	for (int i = 0; i < len - 1; ++i) {
		out << buffer.path[i].getName() << ", ";
	}

	out << buffer.path[len - 1].getName() << " } - " << buffer.weight;
}



std::vector<std::string> Parser::split(const std::string& line, const std::string& delimeters) {
	std::vector<std::string> res;

	std::istringstream iss(line);
	std::string token;

	char c;
	while (iss.get(c)) {
		if (delimeters.find(c) != std::string::npos) {
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