#include <stdexcept>

#include "parser.hpp"

Graph Parser::read(std::istream& in, const std::string& delimiters) {
    Graph result;

    std::string line;
    while(std::getline(in, line)) {
        std::vector<std::string> temp = parse(split(trim(line), delimiters));

        result.addEdge(temp[0], temp[1], std::stoi(temp[2]));
        result.addEdge(temp[1], temp[0], std::stoi(temp[2]));
    }

    return result;
}

std::string Parser::trim(const std::string& line) noexcept {
	std::string result;

	// Пропускаем символы ' ' и '\t'
	std::string whitespace{ " \t" };

	size_t first = line.find_first_not_of(whitespace);
	if (first == std::string::npos) {
		return result;
	}

	size_t last = line.find_last_not_of(whitespace);

	result = line.substr(first, (last - first) + 1);

	return result;
}

std::string Parser::split(const std::string& line, const std::string& delimiters) noexcept {
	std::string result;

	bool need_space = false;
	for (char symbol : line) {
		if (delimiters.find(symbol) != std::string::npos) {
			need_space = true;
		}

		else {
			if (need_space) {
				result += ' ';
				need_space = false;
			}

			result += symbol;
		}
	}

	return result;
}

std::vector<std::string> Parser::parse(const std::string& line) noexcept {
	std::vector<std::string> result;

	size_t first = 0;
	// Парсим значения, которые отделены ' '
	size_t last = line.find(' ');

	while (last != std::string::npos) {
		result.push_back(line.substr(first, last - first));
		first = last + 1;
		last = line.find(' ', first);
	}
	result.push_back(line.substr(first));

	return result;
}