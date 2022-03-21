#ifndef GRAPH_EULER_INL
#define GRAPH_EULER_INL
#include "graph.h"

template<typename Type>
bool Graph<Type>::EulerGraph_() const {
    int OddVertex = 0;
    size_t size = m_adjacency_matrix.size();

    for (int i = 0; i < size; ++i)
    {
        if (m_adjacency_list[i].size() % 2 == 1){
            OddVertex++;
        }
    }

    if (OddVertex > 2)
        return false;

    std::vector<bool> visited(size, false);

    for (int i = 0; i < size; i++){
        if (!m_adjacency_list[i].empty()){
            DfsForEuler(i, visited, size);
            break;
        }
    }

    for (int i = 0; i < size; i++){
        if (!m_adjacency_list[i].empty() && !visited[i])
            return false;
    }

    return true;
}

template<typename Type>
std::string Graph<Type>::IsEulerGraph() const {
    std::stringstream buffer;
    if (EulerGraph_()){
        buffer << "This graph has an Euler cycle." << std::endl;
    }
    else {
        buffer << "This graph has not an Euler cycle!" << std::endl;
    }
    return buffer.str();
}

template<typename Type>
void Graph<Type>::DfsForEuler(int i, std::vector<bool> &visited, const size_t size) const {
    if (visited[i]){
        return;
    }

    visited[i] = true;

    if (i == size){
        return;
    }

    for (auto neighbour : m_adjacency_list[i] ) {
        DfsForEuler(neighbour, visited, size);
    }
}

#endif //GRAPH_EULER_INL