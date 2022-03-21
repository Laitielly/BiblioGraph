project(GraphLibrary)

add_library(GraphLibrary graph.h graph.inl algorithms.inl bfs.inl dfs.inl eccenticity.inl tree.inl independence.inl coloring.inl euler.inl)

target_include_directories(GraphLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
