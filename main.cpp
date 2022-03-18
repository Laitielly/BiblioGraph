#include "graph.h"
#include <iostream>

int main() {
    const Graph<std::string>a(AdjacencyList::LIST,{
                                      {"a",{"b","c","d"}},
                                      {"b",{"a","c"}},
                                      {"c",{"a","b","d","f"}},
                                      {"d",{"a","c","e"}},
                                      {"e",{"d","f","h"}},
                                      {"f",{"c","e"}},
                                      {"h",{"e"}}
                });

//    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance("a","d");
//    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
//    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree("e");
//    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
//    std::cout << a.MaxClique() << a.SizeClique(3);
//    std::cout << a.FindCycles() << a.FindCyclesSize(3);
    std::cout << a.GiveCentralVerticles();
    
    return 0;
}
