#ifndef GRAPH_DFS_INL
#define GRAPH_DFS_INL
#include "graph.h"

void DFS1(int cur, std::list<int> &path, std::vector<int> &used, const std::vector<std::vector<int>>& m_adjacency_list) {
    used[cur]=1;
    for(auto i: m_adjacency_list[cur]){
        if(!used[i]){
            DFS1(i,path,used,m_adjacency_list);
        }
    }
    path.push_front(cur);
}

void DFS2(int cur, std::vector<int> &used, std::vector<std::vector<int>> &trList, int c, std::vector<std::vector<int>> &components){
    used[cur]=1;
    for(auto i: trList[cur]){
        if(!used[i]){
            DFS2(i,used,trList, c, components);
        }
    }
    components[c].push_back(cur);
}

template<typename Type>
std::vector<std::vector<int>> Graph<Type>::StrongConnectivityComponents_() const {
    int verticesNumber = m_vertices.size();
    std::vector<std::vector<int>> trList(verticesNumber);
    std::vector<std::vector<int>> components;
    for(int i=0; i<verticesNumber; ++i){
        int neighbors = m_adjacency_list[i].size();
        for(int j=0; j<neighbors; ++j){
            trList[m_adjacency_list[i][j]].push_back(i);
        }
    }
    std::list<int>path;
    std::vector<int> used(verticesNumber);

    for(int i=0; i<verticesNumber; ++i) {
        if(!used[i]) {
            DFS1(i, path, used, m_adjacency_list);
        }
    }

    std::vector<int> used2(verticesNumber);

    int c=0;
    for(auto i: path){
        if(!used2[i]){
            components.push_back({});
            DFS2(i, used2, trList, c, components);
            ++c;
        }
    }

    return components;
}


template<typename Type>
std::string Graph<Type>::StrongConnectivityComponents() const {
    std::stringstream buffer;
    std::vector<std::vector<int>> components = StrongConnectivityComponents_();
    int componentsCounter = components.size();
    buffer << "The graph has " << componentsCounter <<" strong connectivity components:"<< std::endl;
    for(int i=0; i<componentsCounter; ++i){
        int CurrentComponentCounter = components[i].size();
        buffer << i+1 <<": ";
        for(int j=0; j<CurrentComponentCounter; ++j){
            if(j!=CurrentComponentCounter-1) {
                buffer << m_to_names.at(components[i][j]) << ", ";
            }else{
                buffer << m_to_names.at(components[i][j]);
            }
        }
        buffer << std::endl;
    }
    return buffer.str();
}
#endif //GRAPH_DFS_INL