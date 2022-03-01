#include "graph.h"
#include <iostream>
int main() {
    Graph<char>a(AdjacencyList::LIST, {
            {'a', {'b'}},
            {'b',{'c'}},
            {'c',{'e'}},
            {'e',{'f'}},
            {'f',{'g'}},
            {'g',{}}
    });
    std::cout << a.Distance('a','g');
    return 0;
}
