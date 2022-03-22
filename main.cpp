#include "graph.h"
#include "point.h"
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    const Graph<std::string> a(MatrixType::ADJACENCY, {
                                {0, 0, 0, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0}
    },
                         {"a","b","c","d"}
    );

//    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets();
//    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
//    std::cout << a.PrintAdjacencyList();
//    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
//    std::cout << a.MaxClique() << a.SizeClique(2);
//    std::cout << a.FindCycles() << a.FindCyclesSize(3);
//    std::cout << a.FindCentralVertices();
//    std::cout << a.FindDiameter();
//    std::cout << a.FindRadius();
//    std::cout << a.IsTree();
//    std::cout << a.MaxIndependentSet();
//    std::cout << a.IndependentSetSize(0);
//    std::cout << a.IndependentSetSize(1);
//    std::cout << a.IndependentSetSize(2);
//    std::cout << a.IndependentSetSize(3);
//    std::cout << a.IndependentSetSize(4);
//    std::cout << a.IndependentSetSize(9);
    std::cout << a.IsBipartite() << a.OptimalColoring();
//    std::cout << a.IsEulerGraph();
//    std::cout << a.IsHamiltonGraph();

    return 0;
}
