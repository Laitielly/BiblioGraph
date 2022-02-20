#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>


enum class MatrixType {
    INCIDENCE,
    ADJACENCY
};

enum class AdjacencyList {
    LIST
};

template <typename Type>
class Graph{
private:
    std::vector<std::vector<int>> m_adjacency_matrix;
    std::vector<std::vector<int>> m_adjacency_list;
    std::vector<std::pair<int,int>> m_edges;
    std::vector<int> m_vertices;
    std::map<Type,int> m_to_numbers;
    std::map<int, Type> m_to_names;
    void MakeSetRepresentation();
    void MakeListRepresentation();
public:
    Graph(const MatrixType &type, const std::vector<std::vector<int>> &matrix, const std::vector<Type> &vertices);
    Graph(const std::vector<Type> &vertices, const std::vector<std::pair<Type,Type>> &edges);
    Graph(const AdjacencyList &type, const std::vector<std::pair<Type,std::vector<Type>>> &adjacencyList);
    std::string PrintAdjacencyMatrix() const;
    std::string PrintIncidenceMatrix() const;
    std::string PrintSets() const;
    std::string PrintAdjacencyList() const;
    const Graph& Rename(const Type &name, const Type &rename);
    bool IsUndirected() const;
    bool CheckLoops() const;
    int EdgesNumber() const;

};

#include "graph.inl"
#include "algorithms.inl"
#endif //GRAPH_GRAPH_H
