#include "vertex.hpp"

#include <stdexcept>

Vertex::Vertex(const std::string& name) : name(name) {
    if (name.empty()) {
        throw (std::invalid_argument("Name cannot be empty"));
    }
}

std::string Vertex::getName() const noexcept {
    return name;
}

bool Vertex::operator==(const Vertex& rhs) const noexcept {
    return name == rhs.getName();
}

bool Vertex::operator!=(const Vertex& rhs) const noexcept {
    return !operator==(rhs);
}

bool Vertex::operator<(const Vertex& rhs) const noexcept {
    return name < rhs.getName();
}