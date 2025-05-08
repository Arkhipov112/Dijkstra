#include "../dijkstra/dijkstra.hpp"

#include <iostream>

// Moscow Novosibirsk 7
// Moscow Toronto 9
// Moscow Krasnoyarsk 14
// Novosibirsk Toronto 10
// Novosibirsk Omsk 15
// Omsk Toronto  11
// Toronto Krasnoyarsk 2
// Krasnoyarsk Kiev 9
// Kiev Omsk  6

// {Moscow, Toronto, Krasnoyarsk} - 11

int main() {
    Graph graph;
    graph.addEdge("Moscow", "Novosibirsk", 7);
    graph.addEdge("Moscow", "Toronto", 9);
    graph.addEdge("Moscow", "Krasnoyarsk", 14);
    graph.addEdge("Novosibirsk", "Toronto", 10);
    graph.addEdge("Novosibirsk", "Omsk", 15);
    graph.addEdge("Omsk", "Toronto", 11);
    graph.addEdge("Toronto", "Krasnoyarsk", 2);
    graph.addEdge("Krasnoyarsk", "Kiev", 9);
    graph.addEdge("Kiev", "Omsk", 6);

    Way result = Dijkstra::find(graph, "Moscow", "Krasnoyarsk");

    for (int i = 0; i < result.first.size(); ++i) {
        std::cout << result.first[i] << std::endl;
    }
    std::cout << result.second;
}