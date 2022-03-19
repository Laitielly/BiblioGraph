project(GraphLibrary)

add_library(GraphLibrary graph.h graph.inl algorithms.inl bfs.inl dfs.inl
        clique.cpp clique.h cliquepar.cpp timer.cpp timer.h dfcycle.cpp eccenticity.inl tree.inl
        independence.inl coloring.inl)

target_include_directories(GraphLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})