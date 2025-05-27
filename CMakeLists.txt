cmake_minimum_required(VERSION 3.30.4)

set(CMAKE_CXX_STANDARD 14)

project(Dijkstra)

add_subdirectory(
    googletest
)

add_library(
    vertex

    vertex/vertex.cpp
)

add_library(
    path

    path/path.cpp
)

add_library(
    undirected_graph

    undirected_graph/undirected_graph.cpp
)

add_library(
    parser

    parser/parser.cpp
)

add_library(
    dijkstra

    dijkstra/dijkstra.cpp
)

add_executable(
    DijkstraTest

    test/test.cpp
)

target_link_libraries(
    DijkstraTest

    gtest
    gtest_main

    vertex
    path
    undirected_graph

    parser
    
    dijkstra
)