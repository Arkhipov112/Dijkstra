#include "../googletest/googletest/include/gtest/gtest.h"

#include "../parser/parser.hpp"
#include "../dijkstra/dijkstra.hpp"

UndirectedGraph graphInit() {
    UndirectedGraph ug;

    ug.addEdge(Vertex("Moscow"), Vertex("Novosibirsk"), 7);
    ug.addEdge(Vertex("Moscow"), Vertex("Toronto"), 9);
    ug.addEdge(Vertex("Moscow"), Vertex("Krasnoyarsk"), 14);
    ug.addEdge(Vertex("Novosibirsk"), Vertex("Toronto"), 10);
    ug.addEdge(Vertex("Novosibirsk"), Vertex("Omsk"), 15);
    ug.addEdge(Vertex("Omsk"), Vertex("Toronto"), 11);
    ug.addEdge(Vertex("Toronto"), Vertex("Krasnoyarsk"), 2);
    ug.addEdge(Vertex("Krasnoyarsk"), Vertex("Kiev"), 9);
    ug.addEdge(Vertex("Kiev"), Vertex("Omsk"), 6);
    
    return ug;    
}

TEST(UndirectedGraphTest, AddEdge_FindVertex_FindEdge) {
    UndirectedGraph ug = graphInit();

    EXPECT_TRUE(ug.findVertex(Vertex("Moscow")));
    EXPECT_TRUE(ug.findVertex(Vertex("Novosibirsk")));
    EXPECT_TRUE(ug.findVertex(Vertex("Toronto")));
    EXPECT_TRUE(ug.findVertex(Vertex("Krasnoyarsk")));
    EXPECT_TRUE(ug.findVertex(Vertex("Omsk")));
    EXPECT_TRUE(ug.findVertex(Vertex("Kiev")));

    EXPECT_FALSE(ug.findVertex(Vertex("Abakan")));
    EXPECT_FALSE(ug.findVertex(Vertex("Ivanovo")));

    EXPECT_TRUE(ug.findEdge(Vertex("Moscow"), Vertex("Novosibirsk")));
    EXPECT_TRUE(ug.findEdge(Vertex("Moscow"), Vertex("Toronto")));
    EXPECT_TRUE(ug.findEdge(Vertex("Moscow"), Vertex("Krasnoyarsk")));
    EXPECT_TRUE(ug.findEdge(Vertex("Toronto"), Vertex("Novosibirsk")));
    EXPECT_TRUE(ug.findEdge(Vertex("Omsk"), Vertex("Novosibirsk")));

    EXPECT_FALSE(ug.findEdge(Vertex("Omsk"), Vertex("Krasnoyarsk")));
    EXPECT_FALSE(ug.findEdge(Vertex("Novosibirsk"), Vertex("Krasnoyarsk")));
}

TEST(GraphTest, AddEdge_NegativeWeight) {
    UndirectedGraph ug = graphInit();

    EXPECT_THROW(ug.addEdge(Vertex("Moscow"), Vertex("Novosibirsk"), -7), std::invalid_argument);
    EXPECT_THROW(ug.addEdge(Vertex("Kiev"), Vertex("Omsk"), -6), std::invalid_argument);
}

TEST(GraphTest, GetWeight) {
    UndirectedGraph ug = graphInit();

    EXPECT_EQ(ug.getWeight(Vertex("Moscow"), Vertex("Novosibirsk")), 7);
    EXPECT_EQ(ug.getWeight(Vertex("Moscow"), Vertex("Toronto")), 9);
    EXPECT_EQ(ug.getWeight(Vertex("Omsk"), Vertex("Kiev")), 6);

    EXPECT_THROW(ug.getWeight(Vertex("Moscow"), Vertex("Omsk")), std::invalid_argument);
}

TEST(GraphTest, GetVertexes) {
    UndirectedGraph ug = graphInit();

    EXPECT_EQ(ug.getVertices().size(), 6);
    EXPECT_EQ(ug.getVertices()[0], Vertex("Kiev"));
    EXPECT_EQ(ug.getVertices()[1], Vertex("Krasnoyarsk"));
    EXPECT_EQ(ug.getVertices()[2], Vertex("Moscow"));
    EXPECT_EQ(ug.getVertices()[3], Vertex("Novosibirsk"));
    EXPECT_EQ(ug.getVertices()[4], Vertex("Omsk"));
    EXPECT_EQ(ug.getVertices()[5], Vertex("Toronto"));
}

TEST(GraphTest, GetNeighbors) {
    UndirectedGraph ug = graphInit();

    EXPECT_EQ(ug.getNeighbors(Vertex("Novosibirsk")).size(), 3);
    EXPECT_EQ(ug.getNeighbors(Vertex("Novosibirsk"))[0], Vertex("Moscow"));
    EXPECT_EQ(ug.getNeighbors(Vertex("Novosibirsk"))[1], Vertex("Omsk"));
    EXPECT_EQ(ug.getNeighbors(Vertex("Novosibirsk"))[2], Vertex("Toronto"));
}

TEST(ParserTest, Read) {
    std::istringstream iss(
        "\tMoscow, -Novosibirsk. 7 \n" \
        "\tMoscow, -Toronto. 9 "
    );

    UndirectedGraph ug = Parser::read(iss, " \t,.-");
    EXPECT_EQ(ug.getWeight(Vertex("Moscow"), Vertex("Novosibirsk")), 7);
    EXPECT_EQ(ug.getWeight(Vertex("Moscow"), Vertex("Toronto")), 9);
}

TEST(ParserTest, Write) {
    std::ostringstream oss;
    Path p = { { Vertex("Moscow"), Vertex("Toronto"), Vertex("Krasnoyarsk") }, 11 };

    Parser::write(oss, p);
    EXPECT_EQ(oss.str(), "{ Moscow, Toronto, Krasnoyarsk } - 11");
}

TEST(DijkstraTest, FindPath) {
    UndirectedGraph ug_1 = graphInit();

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