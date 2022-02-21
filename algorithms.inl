#ifndef GRAPH_ALGORITHMS_INL
#define GRAPH_ALGORITHMS_INL
#include "graph.h"

template<typename Type>
bool Graph<Type>::IsUndirected() const {
    int size = m_adjacency_matrix.size();
    for(int i=0; i<size; ++i){
        for(int j=i; j<size; ++j){
            if (m_adjacency_matrix[i][j]!=m_adjacency_matrix[j][i]){
                return false;
            }
        }
    }
    return true;
}

template<typename Type>
bool Graph<Type>::CheckLoops() const {
    int size = m_adjacency_matrix.size();
    for(int i=0; i<size; ++i) {
        if (m_adjacency_matrix[i][i]){
            return true;
        }
    }
    return false;
}

template<typename Type>
int Graph<Type>::EdgesNumber() const {
    return m_edges.size();
}

template<typename Type>
const Graph<Type> &Graph<Type>::Complement() {
    int size = m_adjacency_matrix.size();
    for(int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            if(i!=j) {
                if (m_adjacency_matrix[i][j]) {
                    m_adjacency_matrix[i][j] = 0;
                } else {
                    m_adjacency_matrix[i][j] = 1;
                }
            }
        }
    }
    m_adjacency_list.clear();
    m_edges.clear();
    MakeSetRepresentation();
    MakeListRepresentation();
    return *this;
}


#endif //GRAPH_ALGORITHMS_INL