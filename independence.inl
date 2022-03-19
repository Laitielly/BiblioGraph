#ifndef GRAPH_INDEPENDENCE_INL
#define GRAPH_INDEPENDENCE_INL
#include "graph.h"
template<typename Type>
std::string Graph<Type>::MaxIndependentSet() const {
    std::stringstream buffer;
    std::vector<std::vector<int>> newMatrix = m_adjacency_matrix;
    int size = newMatrix.size();
    std::vector<std::pair<int,int>> edg;
    std::vector<std::vector<int>> lst(size);
    for(int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            if(i!=j) {
                if (newMatrix[i][j]) {
                    newMatrix[i][j] = 0;
                } else {
                    newMatrix[i][j] = 1;
                    edg.push_back({i, j});
                    lst[i].push_back(j);
                }
            }
        }
    }
    GreedMaxClique clique(newMatrix, edg, lst);
    CliqueControl result = clique.Start(CliqueMethod::MaxClique,0);
    if(result == CliqueControl::IsFind){
        std::list<int> maxClique = clique.TakeMaxClique();
        int size = maxClique.size();
        buffer << "Maximum independent set has size is equal to " << size <<"."<<std::endl;
        buffer << "MaximumIndependentSet = {";
        int j=0;
        for (auto iter : maxClique)
        {
            if (j!=size - 1){
                buffer << m_to_names.at(iter) << ", ";
            } else {
                buffer << m_to_names.at(iter) << "}.";
            }
            ++j;
        }
        buffer << std::endl;
    }else if(result == CliqueControl::TimeLimit){
        buffer << "It is impossible to find the maximum independent set! Time limit!" << std::endl;
    }
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::IndependentSetSize(const int n) const {
    std::stringstream buffer;
    if (n >=1 && n <= m_vertices.size()) {
        std::vector<std::vector<int>> newMatrix = m_adjacency_matrix;
        int size = newMatrix.size();
        std::vector<std::pair<int,int>> edg;
        std::vector<std::vector<int>> lst(size);
        for(int i=0; i<size; ++i){
            for(int j=0; j<size; ++j){
                if(i!=j) {
                    if (newMatrix[i][j]) {
                        newMatrix[i][j] = 0;
                    } else {
                        newMatrix[i][j] = 1;
                        edg.push_back({i, j});
                        lst[i].push_back(j);
                    }
                }
            }
        }
        GreedMaxClique clique(newMatrix, edg, lst);
        CliqueControl result = clique.Start(CliqueMethod::CliqueWithKey, n);
        if (result == CliqueControl::IsFind) {
            std::vector<std::vector<int>> sizeClique = clique.TakeSizeClique();
            int sizeClique_size = sizeClique.size();
            buffer << "Independent sets with size " << n << ":" <<std::endl;
            for (int i=0; i<sizeClique_size; ++i) {
                buffer << i+1 <<": ";
                int cur = sizeClique[i].size();
                for (int j=0; j<cur; ++j) {
                    if (j != cur-1) {
                        buffer << m_to_names.at(sizeClique[i][j]) << ", ";
                    } else {
                        buffer << m_to_names.at(sizeClique[i][j]) ;
                    }
                }
                buffer << std::endl;
            }
        } else if (result == CliqueControl::TimeLimit) {
            buffer << "It is impossible to find the maximum independent set! Time limit!" << std::endl;
        } else if (result == CliqueControl::CannotFind) {
            buffer << "Independent set with size " << n << " doesn't exist!" << std::endl;
        }
    } else{
        buffer << "Independent set with size " << n << " it cannot be in a graph with " << m_vertices.size() << " vertices!" << std::endl;
    }
    return buffer.str();
}

#endif //GRAPH_INDEPENDENCE_INL