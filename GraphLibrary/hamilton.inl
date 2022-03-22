#ifndef GRAPH_HAMILTON_INL
#define GRAPH_HAMILTON_INL
#include "graph.h"

template<typename Type>
bool Graph<Type>::IsSafe(int v, std::vector<int> &path, int pos) const {
    if (!m_adjacency_matrix[path[pos - 1]][v])
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

template<typename Type>
bool Graph<Type>::HamiltonGraph_(std::vector<int> &path, int pos) const
{
    size_t size = m_adjacency_matrix.size();
    if (pos == size)
    {
        return bool(m_adjacency_matrix[path[pos - 1]][path[0]]);
    }
    for (int v = 1; v < size; v++)
    {
        if (IsSafe(v, path, pos))
        {
            path[pos] = v;
            if (HamiltonGraph_(path, pos + 1) == true)
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

template<typename Type>
std::string Graph<Type>::IsHamiltonGraph() const{
    size_t size = m_adjacency_matrix.size();
    std::vector<int> path(size, -1);
    path[0] = 0;

    std::stringstream buffer;
    if(HamiltonGraph_(path, 1)){
        buffer << "В графе есть гамильтонов цикл.";
    }
    else {
        buffer << "В графе нет гамильтонова цикла." << std::endl;
    }
    return buffer.str();
}

#endif //GRAPH_HAMILTON_INL