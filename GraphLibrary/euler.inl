#ifndef GRAPH_EULER_INL
#define GRAPH_EULER_INL
#include "graph.h"

template<typename Type>
bool Graph<Type>::IsEulerGraph_() const {
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
    if (IsEulerGraph_()){
        buffer << "This graph has an Euler cycle." << std::endl;
    }
    else {
        buffer << "There is no Euler cycle." << std::endl;
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
bool Graph<Type>::HamCycleUtil(std::vector<int> &path, int pos) const
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
            if (HamCycleUtil (path, pos + 1) == true)
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

template<typename Type>
std::string Graph<Type>::HamCycle() const{
    size_t size = m_adjacency_matrix.size();
    std::vector<int> path(size, -1);
    path[0] = 0;

    std::stringstream buffer;
    if(HamCycleUtil(path, 1)){
        buffer << "There is Hamilton cycle: ";

        for (int i = 0; i < size; i++)
            buffer << path[i] << " -> " ;
        buffer << path[0] << std::endl;
    }
    else {
        buffer << "There is no Hamilton cycle." << std::endl;
    }
    return buffer.str();
}

#endif //GRAPH_EULER_INL