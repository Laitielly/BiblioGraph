#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <map>
#include <sstream>
#include <queue>
#include <list>
#include "clique.h"

enum class MatrixType {
    INCIDENCE,
    ADJACENCY,
};

enum class AdjacencyList {
    LIST,
};

enum class Tree {
    IsTree,
    NotTree
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
    bool IsUndirected_() const;
    bool CheckLoops_() const;
    int PrintVertexDegree_(const Type& name) const;
    std::list<int> Distance_(int start, int end) const;
    std::vector<std::vector<int>>WeakConnectivityComponents_() const;
    std::vector<std::vector<int>>StrongConnectivityComponents_() const;
    int Eccentricity_(int name) const;
    std::pair<int, std::vector<int>> FindRadius_() const;
    Tree IsTree_() const;
    bool IsBipartite_(std::vector<int> &color) const;
    std::vector<int> OptimalColoring_() const;
    bool IsEulerGraph_() const;
    void DfsForEuler(int i, std::vector<bool> &visited, const size_t size) const;
//    std::vector<int> IsGamilgton_() const;
//    void SwapHamilton(int i, std::vector<int> &q) const;
//    void ChangeVectorToTop(std::vector<int> &q) const;
    bool IsSafe(int v, std::vector<int> &path, int pos) const;
    bool hamCycle_() const;
    bool hamCycleUtil(std::vector<int> &path, int pos) const;
public:
    Graph(const MatrixType &type, const std::vector<std::vector<int>> &matrix, const std::vector<Type> &vertices);
    Graph(const std::vector<Type> &vertices, const std::vector<std::pair<Type,Type>> &edges);
    Graph(const AdjacencyList &type, const std::vector<std::pair<Type,std::vector<Type>>> &adjacencyList);
    std::string PrintAdjacencyMatrix() const;
    std::string PrintIncidenceMatrix() const;
    std::string PrintSets() const;
    std::string PrintAdjacencyList() const;
    const Graph& Rename(const Type &name, const Type &rename);
    std::string IsUndirected() const;
    std::string CheckLoops() const;
    std::string EdgesNumber() const;
    std::string VerticesNumber() const;
    const Graph& Complement();
    std::string PrintVertexDegree(const Type& name) const;
    std::string Distance(const Type& start, const Type& end) const;
    std::string WeakConnectivityComponents() const;
    std::string StrongConnectivityComponents() const;
    std::string MaxClique() const;
    std::string SizeClique(const int size) const;
    std::string FindCycles() const;
    std::string FindCyclesSize (const int n) const;
    std::string Eccentricity(const Type &name) const;
    std::string FindDiameter() const;
    std::string FindRadius() const;
    std::string FindCentralVertices() const;
    std::string IsTree() const;
    std::string MaxIndependentSet() const;
    std::string IndependentSetSize (const int n) const;
    std::string IsBipartite() const;
    std::string OptimalColoring() const;
    std::string IsEulerGraph() const;
    std::string IsGamilgton() const;
    //void printSolution(int path[]);
    std::string hamCycle () const;
};

#include "graph.inl"
#include "algorithms.inl"
#include "bfs.inl"
#include "dfs.inl"
#include "eccenticity.inl"
#include "tree.inl"
#include "independence.inl"
#include "coloring.inl"
#include "euler.inl"
#endif //GRAPH_GRAPH_H
