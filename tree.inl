#ifndef GRAPH_TREE_INL
#define GRAPH_TREE_INL
#include "graph.h"

template<typename Type>
Tree Graph<Type>::CheckOnTrees_() const {
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
std::string Graph<Type>::CheckOnTrees() const {
    std::stringstream buffer;
    auto result = CheckOnTrees_();

    if (result == Tree::IsTree)
    {
        buffer << "This graph is definitely a tree." << std::endl;
    } else {
        buffer << "Definitely this graph is not a tree." << std::endl;
    }

    return buffer.str();
}

#endif //GRAPH_TREE_INL