cmake_minimum_required(VERSION 3.30.4)

set(CMAKE_CXX_STANDARD 14)

project(Dijkstra)

add_subdirectory(
    googletest
)

add_library(
    dijkstra
    dijkstra/dijkstra.cpp
    dijkstra/dijkstra.hpp
)

add_library(
    parser
    parser/parser.cpp
    parser/parser.hpp
)

add_executable(
    DijkstraTest
    test/test.cpp
)

target_link_libraries(
    DijkstraTest
    gtest
    gtest_main
    parser
    dijkstra
)