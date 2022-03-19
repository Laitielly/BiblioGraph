#include "graph.h"
#include <iostream>

int main() {
    const Graph<char>a(AdjacencyList::LIST,{
                    {'a',{'b','c'}},
                    {'b',{'a'}},
                    {'c',{'a','d'}},
                    {'d',{'c'}}
                });

//    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance("a","d");
//    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
//    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree("e");
//    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
//    std::cout << a.MaxClique() << a.SizeClique(3);
//    std::cout << a.FindCycles() << a.FindCyclesSize(3);
//    std::cout << a.FindCentralVertices();
//    std::cout << a.FindDiameter();
//    std::cout << a.FindRadius();
//    std::cout << a.Eccentricity("e");
      std::cout << a.IsTree();
    
    return 0;
}
