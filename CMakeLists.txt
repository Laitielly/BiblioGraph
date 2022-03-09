cmake_minimum_required(VERSION 3.20)
project(Graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(Graph main.cpp graph.h graph.inl algorithms.inl bfs.inl dfs.inl)
