#include "graph.h"
#include "point.h"
#include <iostream>

int main() {
//    const Graph<char>a(AdjacencyList::LIST,{
//                    {'a',{'b','e','d'}},
//                    {'b',{'a','c','f'}},
//                    {'c',{'b','d','h'}},
//                    {'d',{'a','c','g'}},
//                    {'e',{'a','f','g'}},
//                    {'f',{'b','e','h'}},
//                    {'h',{'c','f','g'}},
//                    {'g',{'e','h','d'}}
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

    const Graph<Point> a(MatrixType::ADJACENCY, {
            {1, 0, 0, 1, 0, 1},
            {0, 0, 0, 1, 1, 1},
            {0, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 0},
            {0, 0, 1, 1, 0, 1},
            {0, 1, 1, 0, 1, 0}
    },
                         {Point(1,2),Point(2,3),Point(3,4),Point(4,5),Point(5,6),Point(6,7)});
    std::cout << a.IsUndirected() << a.EdgesNumber() << a.PrintSets() << a.Distance(Point(1,1),Point(4,5));
    std::cout << a.VerticesNumber() << a.CheckLoops() << a.PrintAdjacencyMatrix() << a.PrintIncidenceMatrix();
    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree(Point(1,1));
    std::cout << a.StrongConnectivityComponents() << a.WeakConnectivityComponents();
    std::cout << a.MaxClique() << a.SizeClique(3);
    std::cout << a.FindCycles() << a.FindCyclesSize(3);
    std::cout << a.FindCentralVertices();
    std::cout << a.FindDiameter();
    std::cout << a.FindRadius();
    std::cout << a.Eccentricity(Point(3,4));
    std::cout << a.IsTree();
    std::cout << a.MaxIndependentSet();
    std::cout << a.IndependentSetSize(0);
    std::cout << a.IndependentSetSize(1);
    std::cout << a.IndependentSetSize(2);
    std::cout << a.IndependentSetSize(3);
    std::cout << a.IndependentSetSize(4);
    std::cout << a.IndependentSetSize(9);
    return 0;
}
