#include "graph.h"
#include <iostream>

int main() {
    const Graph<char>a(AdjacencyList::LIST, {
            {'a', {'b','c'}},
            {'b',{'e','f','c'}},
            {'c',{'d','g'}},
            {'d',{'c','h'}},
            {'e',{'a','f'}},
            {'f',{'g'}},
            {'g',{'f'}},
            {'h',{'g','d'}}
    });
    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance('a','h');
    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree('b');
    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();

    return 0;
}
