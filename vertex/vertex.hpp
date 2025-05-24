#pragma once

#include <string>

class Vertex final {
public:
    Vertex() = default;
    Vertex(const std::string& name);
    std::string getName() const noexcept;
    bool operator==(const Vertex& rhs) const noexcept;
    bool operator!=(const Vertex& rhs) const noexcept;
    bool operator<(const Vertex& rhs) const noexcept;

private:
    std::string name;
};