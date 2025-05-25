#pragma once

#include "../googletest/googletest/include/gtest/gtest.h"

#include "../dijkstra/dijkstra.hpp"

TEST(DijkstraTest, FindPath) {
    UndirectedGraph ug_1;
    ug_1.addEdge(Vertex("Moscow"), Vertex("Novosibirsk"), 7);
    ug_1.addEdge(Vertex("Moscow"), Vertex("Toronto"), 9);
    ug_1.addEdge(Vertex("Moscow"), Vertex("Krasnoyarsk"), 14);
    ug_1.addEdge(Vertex("Novosibirsk"), Vertex("Toronto"), 10);
    ug_1.addEdge(Vertex("Novosibirsk"), Vertex("Omsk"), 15);
    ug_1.addEdge(Vertex("Omsk"), Vertex("Toronto"), 11);
    ug_1.addEdge(Vertex("Toronto"), Vertex("Krasnoyarsk"), 2);
    ug_1.addEdge(Vertex("Krasnoyarsk"), Vertex("Kiev"), 9);
    ug_1.addEdge(Vertex("Kiev"), Vertex("Omsk"), 6);

    Path p_1 = Dijkstra::findPath(ug_1, Vertex("Moscow"), Vertex("Krasnoyarsk"));
    EXPECT_EQ(p_1.path.size(), 3);
    EXPECT_EQ(p_1.path[0], Vertex("Moscow"));
    EXPECT_EQ(p_1.path[1], Vertex("Toronto"));
    EXPECT_EQ(p_1.path[2], Vertex("Krasnoyarsk"));
    EXPECT_EQ(p_1.weight, 11);

    Path p_2 = Dijkstra::findPath(ug_1, Vertex("Kiev"), Vertex("Kiev"));
    EXPECT_EQ(p_2.path.size(), 1);
    EXPECT_EQ(p_2.path[0], Vertex("Kiev"));
    EXPECT_EQ(p_2.weight, 0);

    UndirectedGraph ug_2;
    ug_2.addEdge(Vertex("Moscow"), Vertex("Novosibirsk"), 7);
    ug_2.addEdge(Vertex("Omsk"), Vertex("Toronto"), 11);

    EXPECT_THROW(Dijkstra::findPath(ug_2, Vertex("Moscow"), Vertex("Toronto")), std::invalid_argument);
}