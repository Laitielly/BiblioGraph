#include "graph.h"

int main() {
    const Graph<std::string> b(MatrixType::INCIDENCE, {
            {1,1,0,0,0,0,0,0},
            {-1,0,-1,1,0,0,0,0},
            {0,-1,1,0,1,1,0,0},
            {0,0,0,-1,-1,0,-1,0},
            {0,0,0,0,0,-1,1,2}
    }, {"a","b","c","d","e"});
    std::cout << b.PrintIncidenceMatrix() << b.PrintAdjacencyMatrix() << b.PrintSets()<<b.EdgesNumber();
    return 0;
}
