#include "graph.h"
#include "point.h"
#include <iostream>

int main() {
//    const Graph<int>a(AdjacencyList::LIST,{
//                    {1,{2,5}},
//                    {2,{1,3,4,5}},
//                    {3,{2,4,6,8}},
//                    {4,{2,3,5,6,7}},
//                    {5,{1,2,4,7}},
//                    {6,{3,4,7,8,9}},
//                    {7,{4,5,6,9}},
//                    {8,{3,6,9}},
//                    {9,{6,7,8}}
//                });
//
//    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance('a','b');
//    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
//    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree('c');
//    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
//    std::cout << a.MaxClique() << a.SizeClique(3);
//    std::cout << a.FindCycles() << a.FindCyclesSize(3);
//    std::cout << a.FindCentralVertices();
//    std::cout << a.FindDiameter();
//    std::cout << a.FindRadius();
//    std::cout << a.Eccentricity('b');
//    std::cout << a.IsTree();
//    std::cout << a.MaxIndependentSet();
//    std::cout << a.IndependentSetSize(0);
//    std::cout << a.IndependentSetSize(1);
//    std::cout << a.IndependentSetSize(2);
//    std::cout << a.IndependentSetSize(3);
//    std::cout << a.IndependentSetSize(4);
//    std::cout << a.IndependentSetSize(9);
//
    const Graph<std::string> a(MatrixType::ADJACENCY, {
                                {0, 1, 0, 1},
                                {1, 0, 1, 0},
                                {0, 1, 0, 1},
                                {1, 0, 1, 0}
    },
                         {"a","b","c","d"});
    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets();
    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
    std::cout << a.PrintAdjacencyList();
    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
    std::cout << a.MaxClique() << a.SizeClique(2);
    std::cout << a.FindCycles() << a.FindCyclesSize(3);
    std::cout << a.FindCentralVertices();
    std::cout << a.FindDiameter();
    std::cout << a.FindRadius();
    std::cout << a.IsTree();
    std::cout << a.MaxIndependentSet();
    std::cout << a.IndependentSetSize(0);
    std::cout << a.IndependentSetSize(1);
    std::cout << a.IndependentSetSize(2);
    std::cout << a.IndependentSetSize(3);
    std::cout << a.IndependentSetSize(4);
    std::cout << a.IndependentSetSize(9);
    std::cout << a.IsBipartite() << a.OptimalColoring();
    std::cout << a.IsEulerGraph();

    return 0;
}
