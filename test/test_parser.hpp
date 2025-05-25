#pragma once

#include "../googletest/googletest/include/gtest/gtest.h"

#include "../parser/parser.hpp"

TEST(ParserTest, Read) {
    std::istringstream iss(
        "test\n"                       \
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