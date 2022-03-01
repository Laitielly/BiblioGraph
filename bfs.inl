#ifndef GRAPH_BFS_INL
#define GRAPH_BFS_INL
#include "graph.h"

template<typename Type>
std::list<int> Graph<Type>::Distance_(int start, int end) const {
    if(!(start<m_adjacency_list.size() and start >= 0 and end < m_adjacency_list.size() and end >= 0)){
        throw std::runtime_error("The number passed to the Distance_ function exceeds the allowed value!");
    }
    std::vector<int> used(m_adjacency_list.size(),-1);
    std::queue<int> queue;
    queue.push(start);
    used[start] = start;
    while (!queue.empty()) {
        int current = queue.front(), neighbors = m_adjacency_list[current].size();
        queue.pop();
        for (int i = 0; i < neighbors; ++i) {
            int currentNeighbour = m_adjacency_list[current][i];
            if (used[currentNeighbour] == -1) {
                queue.push(currentNeighbour);
                used[currentNeighbour] = current;
            }
            if (currentNeighbour == end) {
                break;
            }
        }
    }
    std::list<int> path;
    if(used[end]==-1){
        path.push_front(-1);
    }
    else{
        int current = end;
        while(current!=start){
            path.push_front(current);
            current=used[current];
        }
        path.push_front(start);
    }
    return path;
}

template<typename Type>
std::string Graph<Type>::Distance(const Type &start, const Type &end) const {
    std::stringstream buffer;
    if(m_to_numbers.find(start)!=m_to_numbers.end() and m_to_numbers.find(end)!=m_to_numbers.end()){
        std::list<int> path = Distance_(m_to_numbers.at(start), m_to_numbers.at(end));
        if(path.front()!=-1){
            buffer << "Distance from "<< start <<" to " << end <<" is equal to "<< path.size()-1 << "." << std::endl;
            buffer << "Path from "<< start <<" to "<< end <<":" << std::endl;
            int pathSize=path.size(), counter = 0;
            for(auto i: path){
                ++counter;
                if (counter==pathSize){
                    buffer<<m_to_names.at(i);
                }else{
                    buffer<<m_to_names.at(i)<<" -> ";
                }
            }
            buffer << std::endl;
        }else{
            buffer << "There is no way to get from "<< start << " to " << end << "." << std::endl;
        }
    }
    else{
        buffer << "A nonexistent vertex was passed to the function Distance!" << std::endl;
    }
    return buffer.str();
}

#endif //GRAPH_BFS_INL