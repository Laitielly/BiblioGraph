#include "graph.h"

int main() {
//    const Graph <std::string> a({"a","b","c"},{{"a","c"},{"a","b"}, {"b","a"}, {"a","a"}});
//    a.PrintSets().PrintAdjacencyList().PrintIncidenceMatrix().PrintAdjacencyMatrix();
//    std::cout << std::boolalpha<<" " <<a.IsUndirected() <<" "<<a.CheckLoops() <<" " <<a.EdgesNumber() <<std::endl;
//    std::cout << a.PrintAdjacencyMatrix();
//    std::cout << a.PrintAdjacencyList()<< a.PrintIncidenceMatrix() << a.PrintAdjacencyMatrix() << a.PrintSets();
    const Graph<std::string> b(MatrixType::INCIDENCE, {
            {1,2,1,0},
            {1,0,0,2},
            {0,0,-1,0}
    }, {"a","b","c"});
    std::cout << b.PrintAdjacencyMatrix() << b.PrintSets();
    return 0;
}
