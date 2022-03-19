#include "graph.h"
#include <iostream>

int main() {
    const Graph<char>a(AdjacencyList::LIST,{
                    {'a',{'b','e','d'}},
                    {'b',{'a','c','f'}},
                    {'c',{'b','d','h'}},
                    {'d',{'a','c','g'}},
                    {'e',{'a','f','g'}},
                    {'f',{'b','e','h'}},
                    {'h',{'c','f','g'}},
                    {'g',{'e','h','d'}}
                });

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
    std::cout << a.MaxIndependentSet();
    std::cout << a.IndependentSetSize(0);
    std::cout << a.IndependentSetSize(1);
    std::cout << a.IndependentSetSize(2);
    std::cout << a.IndependentSetSize(3);
    std::cout << a.IndependentSetSize(4);
    std::cout << a.IndependentSetSize(9);
    
    return 0;
}
