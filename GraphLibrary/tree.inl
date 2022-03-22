#ifndef GRAPH_TREE_INL
#define GRAPH_TREE_INL
#include "graph.h"

template<typename Type>
Tree Graph<Type>::IsTree_() const {
    auto a = WeakConnectivityComponents_();
    GreedMaxClique cycle(m_adjacency_matrix, m_edges, m_adjacency_list);
    CyclicityResult result = cycle.Cyclicity();

     if (a.size() == 1 && result == CyclicityResult::NoneCycle)
     {
         return Tree::IsTree;
     }

    return Tree::NotTree;
}

template<typename Type>
std::string Graph<Type>::IsTree() const {
    std::stringstream buffer;
    auto result = IsTree_();

    if (result == Tree::IsTree)
    {
        buffer << "Этот граф является деревом." << std::endl;
    } else {
        buffer << "Этот граф не является деревом." << std::endl;
    }

    return buffer.str();
}

#endif //GRAPH_TREE_INL