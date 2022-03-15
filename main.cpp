#include "graph.h"
#include <iostream>

int main() {
    const Graph<std::string>a(MatrixType::ADJACENCY,{
                        {0,0,1,1,1},
                        {1,0,0,0,1},
                        {1,1,1,0,0},
                        {1,0,1,0,1},
                        {0,0,1,0,1}
                },
                {"a","b","c","d","e"});

    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance("a","d");
    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree("e");
    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
    std::cout << a.MaxClique() << a.SizeClique(3);
    std::cout << a.FindCycles() << a.FindCyclesSize(3);
    
    return 0;
}
