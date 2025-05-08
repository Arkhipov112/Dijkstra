#pragma once
#include <map>
#include <string>
#include <vector>

struct Graph final {
    public:
        void addEdge(const std::string& from, const std::string& to, int distance);
        bool findVertex(const std::string& vertex) const noexcept;
        bool findEdge(const std::string& from, const std::string& to) const noexcept;
        int getDistance(const std::string& from, const std::string& to) const;
        std::vector<std::string> getVertex() const noexcept;
        std::vector<std::string> getNeighbors(const std::string& vertex) const;
    
    private:
        std::map<std::string, std::map<std::string, int>> adjacency;
    };