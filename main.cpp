#include "graph.h"
#include <iostream>
int main() {
    const Graph<char>a(AdjacencyList::LIST, {
            {'a', {'b','c'}},
            {'b',{'e'}},
            {'c',{}},
            {'e',{'f','g'}},
            {'f',{'e'}},
            {'g',{'e','m'}},
            {'k',{}},
            {'l',{}},
            {'m',{'n'}},
            {'n',{'m'}}
    });
    std::cout << a.ConnectivityComponents() << a.Distance('a','n');

    return 0;
}
