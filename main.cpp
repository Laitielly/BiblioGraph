#include "graph.h"
#include <iostream>
int main() {
    Graph<char>a(AdjacencyList::LIST,{
            {'a',{'b','a'}},
            {'b',{'a'}},
            {'d',{'a'}},
            {'e',{'d'}}
    });
    a.Rename('a','c');
    a.Complement();
    std::cout << a.PrintAdjacencyList() << a.PrintVertexDegree('c');
    return 0;
}
