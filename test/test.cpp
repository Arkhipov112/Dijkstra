#include <gtest/gtest.h>

#include "../parser/parser.hpp"
#include "../dijkstra/dijkstra.hpp"

graph graph_init() {
    graph g;

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 3);
    g.add_edge("B", "D", 2);
    g.add_edge("C", "D", 7);
    g.add_edge("D", "E", 1);
    
    return g;    
}

TEST(GraphTest, AddEdgeAndFindVertexAndFindEdge) {
    graph g = graph_init();

    EXPECT_TRUE(g.find_vertex("A"));
    EXPECT_TRUE(g.find_vertex("B"));
    EXPECT_TRUE(g.find_vertex("C"));
    EXPECT_TRUE(g.find_vertex("D"));
    EXPECT_TRUE(g.find_vertex("E"));
    EXPECT_FALSE(g.find_vertex("F"));
    EXPECT_FALSE(g.find_vertex("G"));

    EXPECT_TRUE(g.find_edge("A", "B"));
    EXPECT_TRUE(g.find_edge("A", "C"));
    EXPECT_TRUE(g.find_edge("B", "D"));
    EXPECT_TRUE(g.find_edge("C", "D"));
    EXPECT_TRUE(g.find_edge("D", "E"));
    EXPECT_FALSE(g.find_edge("A", "D"));
    EXPECT_FALSE(g.find_edge("A", "E"));
}

TEST(GraphTest, AddInvalidData) {
    graph g;

    EXPECT_THROW(g.add_edge("A", "B", -5), std::invalid_argument);
    EXPECT_THROW(g.add_edge("B", "C", -1), std::invalid_argument);
}

TEST(GraphTest, GetDistance) {
    graph g = graph_init();

    EXPECT_EQ(g.get_dist("A", "B"), 5);
    EXPECT_EQ(g.get_dist("A", "C"), 3);
    EXPECT_EQ(g.get_dist("B", "D"), 2);
    EXPECT_EQ(g.get_dist("C", "D"), 7);
    EXPECT_EQ(g.get_dist("D", "E"), 1);

    EXPECT_THROW(g.get_dist("A", "D"), std::invalid_argument);
    EXPECT_THROW(g.get_dist("A", "E"), std::invalid_argument);
}

TEST(GraphTest, GetVertexes) {
    graph g = graph_init();

    EXPECT_EQ(g.get_vertexes().size(), 5);
    EXPECT_EQ(g.get_vertexes()[0], "A");
    EXPECT_EQ(g.get_vertexes()[1], "B");
    EXPECT_EQ(g.get_vertexes()[2], "C");
    EXPECT_EQ(g.get_vertexes()[3], "D");
    EXPECT_EQ(g.get_vertexes()[4], "E");
}

TEST(GraphTest, GetNeighbors) {
    graph g = graph_init();

    EXPECT_EQ(g.get_neighbors("A").size(), 2);
    EXPECT_EQ(g.get_neighbors("A")[0], "B");
    EXPECT_EQ(g.get_neighbors("A")[1], "C");
}