#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../dijkstra/dijkstra.hpp"

class Parser final {
public:
	Parser() = delete;

    static Graph read(std::istream& in, const std::string& delimiters);

private:
	// Возвращает строку без отступов слева и справа
	static std::string trim(const std::string& line) noexcept;

	// Заменяет разделительные символы на пробел
	static std::string split(const std::string& line, const std::string& delimiters) noexcept;

	// Возвращает вектор из отдельных значений
	static std::vector<std::string> parse(const std::string& line) noexcept;
};