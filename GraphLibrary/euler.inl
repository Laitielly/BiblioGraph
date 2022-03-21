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


//template<typename Type>
//std::vector<int> Graph<Type>::IsGamilgton_() const {
//    size_t size = m_adjacency_matrix.size();
//    std::vector<int> q(size);
//    for (int i = 0; i < size; ++i) {
//        q[i] = i;
//    }
//
//    size_t cycleSize = size * (size - 1);
//    for (int k = 0; k < cycleSize; k++){
//        if (!m_adjacency_matrix[q[0]][q[1]]){
//            int i = 2;
//            while (!m_adjacency_matrix[q[0]][q[i]] || !m_adjacency_matrix[q[1]][q[i + 1]]){
//                i++;
//                if (i == size) {
//                    q.clear();
//                    return q;
//                }
//            }
//            SwapHamilton(i, q);
//        }
//    }
//    return q;
//}
//
//template<typename Type>
//std::string Graph<Type>::IsGamilgton() const {
//    std::stringstream buffer;
//    auto q = IsGamilgton_();
//    if (q.empty()){
//        buffer << "There is no Hamilton cycle." << std::endl;
//    }
//    else {
//        buffer << "Hamilton cycle exists:" << std::endl << "- " << q[0];
//        size_t size = q.size();
//        for (int i = 1; i < size; i++) {
//            buffer << ", " << q[i];
//        }
//        buffer << std::endl;
//    }
//
//    return buffer.str();
//}
//
//template<typename Type>
//void Graph<Type>::SwapHamilton(int i, std::vector<int> &q) const {
//    int size = i /2;
//    int tmp = 0;
//    for (int j = 1; j < size; ++j) {
//        tmp = q[j];
//        q[j] = q[size - j];
//        q[size - j] = tmp;
//    }
//}
//
//template<typename Type>
//void Graph<Type>::ChangeVectorToTop(std::vector<int> &q) const {
//    size_t size = q.size();
//    if (size <= 1) return;
//    std::vector<int> q2(size - 1);
//    for(int i = 0; i < size - 2; ++i){
//        q2[i] = q[i + 2];
//    }
//    q2[size-2] = q[0];
//    q = q2;
//}

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
bool Graph<Type>::hamCycleUtil(std::vector<int> &path, int pos) const
{
    size_t size = m_adjacency_matrix.size();
    if (pos == size)
    {
        if (m_adjacency_matrix[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }
    for (int v = 1; v < size; v++)
    {
        if (IsSafe(v, path, pos))
        {
            path[pos] = v;
            if (hamCycleUtil (path, pos + 1) == true)
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

template<typename Type>
bool Graph<Type>::hamCycle_() const{
    size_t size = m_adjacency_matrix.size();
    std::vector<int> path(size, -1);
    path[0] = 0;
    if (hamCycleUtil(path, 1) == false ){
        return false;
    }
    return true;
}

template<typename Type>
std::string Graph<Type>::hamCycle() const {
    std::stringstream buffer;
    if(hamCycle_()){
        buffer << "There is Hamilton cycle." << std::endl;
    }
    else {
        buffer << "There is no Hamilton cycle." << std::endl;
    }
    return buffer.str();
}


#endif //GRAPH_EULER_INL