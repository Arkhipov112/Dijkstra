#include <gtest/gtest.h>

#include "../parser/parser.hpp"
#include "../dijkstra/dijkstra.hpp"

// Parser тесты

TEST(ParserTest, ReadCorrectData) {
    std::string text =  "\tMoscow, Novosibirsk, 7\n" \
                        "\tMoscow. Toronto. 9\n" \
                        " Moscow Krasnoyarsk 14\n" \
                        " Novosibirsk Toronto 10\n" \
                        "Novosibirsk, Omsk, 15\n" \
                        "Omsk Toronto  11\n" \
                        "Toronto. Krasnoyarsk. 2\n" \
                        "Krasnoyarsk  Kiev  9\n" \
                        " Kiev Omsk  6\n";


    std::istringstream iss(text);

    Graph result = Parser::read(iss, " ,.");
    
    EXPECT_EQ(result.getDistance("Moscow", "Novosibirsk"), 7);
    EXPECT_EQ(result.getDistance("Moscow", "Toronto"), 9);
    EXPECT_EQ(result.getDistance("Moscow", "Krasnoyarsk"), 14);
    EXPECT_EQ(result.getDistance("Novosibirsk", "Toronto"), 10);
    EXPECT_EQ(result.getDistance("Novosibirsk", "Omsk"), 15);
    EXPECT_EQ(result.getDistance("Omsk", "Toronto"), 11);

    EXPECT_EQ(result.getDistance("Toronto", "Krasnoyarsk"), 2);
    EXPECT_EQ(result.getDistance("Krasnoyarsk", "Kiev"), 9);
    EXPECT_EQ(result.getDistance("Kiev", "Omsk"), 6);
}

TEST(ParserTest, ReadIncorrectData1) {
    std::string text =  "Moscow 7";
    std::istringstream iss(text);

    try {
        Graph result = Parser::read(iss, "");
    }

    catch (const std::exception& exception) {
        EXPECT_STREQ(exception.what(), "Does not match the type");
    }
}

TEST(ParserTest, ReadIncorrectData2) {
    std::string text =  "Moscow Novosibirsk -7";
    std::istringstream iss(text);

    try {
        Graph result = Parser::read(iss, "");
    }

    catch (const std::exception& exception) {
        EXPECT_STREQ(exception.what(), "The distance cannot be negative");
    }
}

// Dijkstra тесты

TEST(DijkstraTest, Find) {
    std::string text =  "Moscow Novosibirsk 7\n" \
                        "Moscow Toronto 9\n" \
                        "Moscow Krasnoyarsk 14\n" \
                        "Novosibirsk Toronto 10\n" \
                        "Novosibirsk Omsk 15\n" \
                        "Omsk Toronto 11\n" \
                        "Toronto Krasnoyarsk 2\n" \
                        "Krasnoyarsk Kiev 9\n" \
                        "Kiev Omsk 6\n";

    std::istringstream iss(text);
    Graph graph = Parser::read(iss, " ,.");

    Path result = Dijkstra::find(graph, "Moscow", "Krasnoyarsk");

    std::vector<std::string> buffer = { "Moscow", "Toronto", "Krasnoyarsk" };

    EXPECT_EQ(result.second, 11);
    EXPECT_EQ(result.first, buffer);
}