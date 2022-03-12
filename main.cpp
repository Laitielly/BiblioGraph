#include "graph.h"
#include <iostream>

int main() {
        Graph<char> a(MatrixType::ADJACENCY,{
            {0,0,0,0},
            {0,0,0,1},
            {0,0,1,0},
            {0,0,0,0}
        },{'a','b','c','d'});
//    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance('a','g');
//    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
//    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree('b');
//    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
    std::cout << a.SizeClique(2);
    return 0;
}
