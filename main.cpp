#include "graph.h"
#include <iostream>

int main() {
        Graph<char> a(MatrixType::ADJACENCY,{
            {1,1,1,1},
            {1,1,1,1},
            {1,1,1,1},
            {1,1,1,1}
        },{'a','b','c','d'});
    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance('a','g');
    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree('b');
    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
    std::cout << a.SizeClique(1);
    return 0;
}
