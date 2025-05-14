#include <gtest/gtest.h>

#include "../parser/parser.hpp"
#include "../dijkstra/dijkstra.hpp"

graph graph_init() {
    graph g;

    g.add_edge("Moscow", "Novosibirsk", 7);
    g.add_edge("Moscow", "Toronto", 9);
    g.add_edge("Moscow", "Krasnoyarsk", 14);
    g.add_edge("Novosibirsk", "Toronto", 10);
    g.add_edge("Novosibirsk", "Omsk", 15);
    g.add_edge("Omsk", "Toronto", 11);
    g.add_edge("Toronto", "Krasnoyarsk", 2);
    g.add_edge("Krasnoyarsk", "Kiev", 9);
    g.add_edge("Kiev", "Omsk", 6);
    
    return g;    
}

TEST(GraphTest, AddEdgeAndFindVertexAndFindEdge) {
    graph g = graph_init();

    EXPECT_TRUE(g.find_vertex("Moscow"));
    EXPECT_TRUE(g.find_vertex("Novosibirsk"));
    EXPECT_TRUE(g.find_vertex("Toronto"));
    EXPECT_TRUE(g.find_vertex("Krasnoyarsk"));
    EXPECT_TRUE(g.find_vertex("Omsk"));
    EXPECT_TRUE(g.find_vertex("Kiev"));

    EXPECT_FALSE(g.find_vertex("Abakan"));
    EXPECT_FALSE(g.find_vertex("Ivanovo"));

    EXPECT_TRUE(g.find_edge("Moscow", "Novosibirsk"));
    EXPECT_TRUE(g.find_edge("Moscow", "Toronto"));
    EXPECT_TRUE(g.find_edge("Moscow", "Krasnoyarsk"));
    EXPECT_TRUE(g.find_edge("Toronto", "Novosibirsk"));
    EXPECT_TRUE(g.find_edge("Omsk", "Novosibirsk"));

    EXPECT_FALSE(g.find_edge("Omsk", "Krasnoyarsk"));
    EXPECT_FALSE(g.find_edge("Novosibirsk", "Krasnoyarsk"));
}

TEST(GraphTest, AddInvalidData) {
    graph g;

    EXPECT_THROW(g.add_edge("Moscow", "Novosibirsk", -7), std::invalid_argument);
    EXPECT_THROW(g.add_edge("Kiev", "Omsk", -6), std::invalid_argument);
}

TEST(GraphTest, GetDistance) {
    graph g = graph_init();

    EXPECT_EQ(g.get_dist("Moscow", "Novosibirsk"), 7);
    EXPECT_EQ(g.get_dist("Moscow", "Toronto"), 9);
    EXPECT_EQ(g.get_dist("Omsk", "Kiev"), 6);

    EXPECT_THROW(g.get_dist("Moscow", "Omsk"), std::invalid_argument);
}

TEST(GraphTest, GetVertexes) {
    graph g = graph_init();

    EXPECT_EQ(g.get_vertexes().size(), 6);
    EXPECT_EQ(g.get_vertexes()[0], "Kiev");
    EXPECT_EQ(g.get_vertexes()[1], "Krasnoyarsk");
    EXPECT_EQ(g.get_vertexes()[2], "Moscow");
    EXPECT_EQ(g.get_vertexes()[3], "Novosibirsk");
    EXPECT_EQ(g.get_vertexes()[4], "Omsk");
    EXPECT_EQ(g.get_vertexes()[5], "Toronto");
}

TEST(GraphTest, GetNeighbors) {
    graph g = graph_init();

    EXPECT_EQ(g.get_neighbors("Novosibirsk").size(), 3);
    EXPECT_EQ(g.get_neighbors("Novosibirsk")[0], "Moscow");
    EXPECT_EQ(g.get_neighbors("Novosibirsk")[1], "Omsk");
    EXPECT_EQ(g.get_neighbors("Novosibirsk")[2], "Toronto");
}

TEST(DijkstraTest, FindPath) {
    graph g_1 = graph_init();

    path res_1 = dijkstra::find_path(g_1, "Moscow", "Krasnoyarsk");
    EXPECT_EQ(res_1.first.size(), 3);
    EXPECT_EQ(res_1.first[0], "Moscow");
    EXPECT_EQ(res_1.first[1], "Toronto");
    EXPECT_EQ(res_1.first[2], "Krasnoyarsk");
    EXPECT_EQ(res_1.second, 11);

    path res_2 = dijkstra::find_path(g_1, "Kiev", "Kiev");
    EXPECT_EQ(res_2.first.size(), 1);
    EXPECT_EQ(res_2.first[0], "Kiev");
    EXPECT_EQ(res_2.second, 0);

    graph g_2;
    g_2.add_edge("Moscow", "Novosibirsk", 7);
    g_2.add_edge("Omsk", "Toronto", 11);

    EXPECT_THROW(dijkstra::find_path(g_2, "Moscow", "Toronto"), std::out_of_range);
}