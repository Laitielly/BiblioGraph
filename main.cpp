#include "graph.h"
#include <iostream>

int main() {
    Graph<int>a(MatrixType::ADJACENCY,{
                        {0,0,0},
                        {0,0,0},
                        {0,0,0}

                },
                {1,2,3});
//    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance(4,9);
//    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
//    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree(4);
//    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
//    std::cout << a.SizeClique(13);
    std::cout << a.Cyclicity();
    return 0;
}
