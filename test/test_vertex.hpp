#pragma once

#include "../googletest/googletest/include/gtest/gtest.h"

#include "../vertex/vertex.hpp"

TEST(VertexTest, Constructor_Getters) {
    EXPECT_EQ(Vertex("A").getName(), "A");
}

TEST(VertexTest, Constructor_EmptyName) {
    EXPECT_THROW(Vertex(""), std::invalid_argument);
}

TEST(VertexTest, OperatorEqual) {
    EXPECT_TRUE(Vertex("A") == Vertex("A"));
    EXPECT_FALSE(Vertex("A") == Vertex("B"));
}

TEST(VertexTest, OperatorNotEqual) {
    EXPECT_FALSE(Vertex("A") != Vertex("A"));
    EXPECT_TRUE(Vertex("A") != Vertex("B"));
}

TEST(VertexTest, OperatorLess) {
    EXPECT_TRUE(Vertex("A") < Vertex("B"));
    EXPECT_FALSE(Vertex("A") < Vertex("A"));
    EXPECT_FALSE(Vertex("B") < Vertex("A"));
}