#pragma once
#include <map>
#include <string>
#include <vector>

class graph final {
public:
    void add_edge(const std::string& from, const std::string& to, int dist);
    
    bool find_vertex(const std::string& vertex) const;
    bool find_edge(const std::string& from, const std::string& to) const;
    
    int get_dist(const std::string& from, const std::string& to) const;
    std::vector<std::string> get_vertexes() const;
    std::vector<std::string> get_neighbors(const std::string& vertex) const;
    
private:
    // Структуру (поменять)
    std::map<std::string, std::map<std::string, int>> adjacency;
};