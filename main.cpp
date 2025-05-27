#include "parser/parser.hpp"
#include "dijkstra/dijkstra.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string file_path;
    std::cout << "File path: ";
    std::cin >> file_path;

    std::string delimeters;
    std::cout << "Delimeters: ";
    std::cin >> delimeters;

    std::string start;
    std::cout << "Start: ";
    std::cin >> start;

    std::string end;
    std::cout << "End: ";
    std::cin >> end;

    std::ifstream ifs(file_path);
    if (!ifs.is_open()) {
        std::cerr << "Could not open the file" << std::endl;
        return 1;
    }

    UndirectedGraph ug = Parser::read(ifs, delimeters);
    Path path = Dijkstra::findPath(ug, Vertex(start), Vertex(end));

    Parser::write(std::cout, path);
}