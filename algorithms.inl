#ifndef GRAPH_ALGORITHMS_INL
#define GRAPH_ALGORITHMS_INL
#include "graph.h"

template<typename Type>
bool Graph<Type>::IsUndirected_() const {
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
std::string Graph<Type>::IsUndirected() const {
    std::stringstream buffer;
    if(IsUndirected_()){
        buffer << "The graph is undirected." << std::endl;
        return buffer.str();
    }else{
        buffer << "The graph is directed." << std::endl;
        return buffer.str();
    }
}

template<typename Type>
bool Graph<Type>::CheckLoops_() const {
    int size = m_adjacency_matrix.size();
    for(int i=0; i<size; ++i) {
        if (m_adjacency_matrix[i][i]){
            return true;
        }
    }
    return false;
}

template<typename Type>
std::string Graph<Type>::CheckLoops() const {
    std::stringstream buffer;
    if(CheckLoops_()){
        buffer << "The graph has loops." << std::endl;
        return buffer.str();
    }else{
        buffer << "The graph has no loop." << std::endl;
        return buffer.str();
    }
}

template<typename Type>
std::string Graph<Type>::EdgesNumber() const {
    std::stringstream buffer;
    int vertices = 0, directed=0, undirected=0, loop=0;
    vertices=m_adjacency_matrix.size();
    for(int i=0; i<vertices; ++i){
        for(int j=i; j<vertices; ++j){
            if(i==j){
                if(m_adjacency_matrix[i][j]==1){
                    ++loop;
                }
            }else{
                if(m_adjacency_matrix[i][j]==1 and m_adjacency_matrix[j][i]==1){
                    ++undirected;
                }
                if(m_adjacency_matrix[i][j]!=m_adjacency_matrix[j][i] and
                    (m_adjacency_matrix[i][j]==1 or m_adjacency_matrix[j][i]==1)){
                        ++directed;
                }
            }
        }
    }
    buffer << "The graph has "<<directed<<" directed edges, "<< undirected <<" undirected edges and "<<loop<<" loops."<<std::endl;
    return buffer.str();
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

template<typename Type>
int Graph<Type>::PrintVertexDegree_(const Type& name) const{
    int adjacencyListSize = m_adjacency_list.size();
    if(m_to_numbers.find(name)!=m_to_numbers.end()) {
        return m_adjacency_list[m_to_numbers.at(name)].size();
    }
    return -1;
}

template<typename Type>
std::string Graph<Type>::PrintVertexDegree(const Type &name) const {
    std::stringstream buffer;
    if(PrintVertexDegree_(name)!=-1){
        buffer << "The degree of vertex " << name << " is equal to " << PrintVertexDegree_(name) << "." << std::endl;
    }else{
        buffer << "Vertex " << name << " does not exist!" << std::endl;
    }
    return buffer.str();
}


template<typename Type>
std::string Graph<Type>::VerticesNumber() const {
    std::stringstream buffer;
    buffer << "The graph has " << m_vertices.size() <<" vertices."<<std::endl;
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::MaxClique() const {
    std::stringstream buffer;
    GreedMaxClique clique(m_adjacency_matrix, m_edges, m_adjacency_list);
    CliqueControl result = clique.Start(CliqueMethod::MaxClique,0);
    if(result == CliqueControl::IsFind){
        std::list<int> maxClique = clique.TakeMaxClique();
        int size = maxClique.size();
        buffer << "Maximum clique has size is equal to " << size <<"."<<std::endl;
        buffer << "MaxClique = {";
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
        buffer << "it is impossible to find the maximum clique! Time limit!" << std::endl;
    }
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::SizeClique(const int size) const {
    std::stringstream buffer;
    if (size >=1 && size <= m_vertices.size()) {
        GreedMaxClique clique(m_adjacency_matrix, m_edges, m_adjacency_list);
        CliqueControl result = clique.Start(CliqueMethod::CliqueWithKey, size);
        if (result == CliqueControl::IsFind) {
            std::vector<std::vector<int>> sizeClique = clique.TakeSizeClique();
            int sizeClique_size = sizeClique.size();
            buffer << "Cliques with size " << size << ":" <<std::endl;
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
            buffer << "it is impossible to find the maximum clique! Time limit!" << std::endl;
        } else if (result == CliqueControl::CannotFind) {
            buffer << "Clique to size " << size << " doesn't exist!" << std::endl;
        }
    } else{
        buffer << "Clique with size " << size << " it cannot be in a graph with " << m_vertices.size() << " vertices!" << std::endl;
    }
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::FindCycles() const {
    std::stringstream buffer;
    GreedMaxClique cycle(m_adjacency_matrix, m_edges, m_adjacency_list);
    CyclicityResult result = cycle.Cyclicity();
    if(result == CyclicityResult::HasCycle){
        buffer << "This graph has cycles." <<std::endl;
    }else if(result == CyclicityResult::NoneCycle){
        buffer << "This graph hasn't cycles!" << std::endl;
    }
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::FindCyclesSize(const int n) const {
    std::stringstream buffer;
    if (n >=3 && n <= m_vertices.size()) {
        GreedMaxClique cycle(m_adjacency_matrix, m_edges, m_adjacency_list);
        CyclicityResult result = cycle.CyclicitySize(n);
        if (result == CyclicityResult::HasCycle) {
            buffer << "This graph has cycles of size " << n <<":" << std::endl;
            std::vector<std::vector<int>> cycles = cycle.TakeSizeCycle();
            int sizeCycle_size = cycles.size();

            for (int i = 0; i < sizeCycle_size; ++i) {
                buffer << i + 1 << ": ";
                int cur = cycles[i].size();
                for (int j = 0; j < cur; ++j) {
                        buffer << m_to_names.at(cycles[i][j]) << " -> ";
                }
                buffer << m_to_names.at(cycles[i][0]);
                buffer << std::endl;
            }
        } else if (result == CyclicityResult::NoneCycle) {
            buffer << "This graph has no cycles of size " << n << ":"<< std::endl;
        } else if (result == CyclicityResult::TimeLimit) {
            buffer << "it is impossible to find cycles of size " << n << " Time limit!" << std::endl;
        }
    }else{
        if (m_adjacency_matrix.size()<3){
            buffer << "There can be no cycles in a graph with " << m_adjacency_matrix.size() <<" vertices." << std::endl;
        }else if(m_adjacency_matrix.size()==3){
            buffer << "A cycles in a graph with 3 vertices can only have length 3." << std::endl;
        }else {
            buffer << "Cycles in a graph with " << m_adjacency_matrix.size() << " vertices can have a length from 3 to "
                   << m_adjacency_matrix.size() << "." << std::endl;
        }
    }
    return buffer.str();
}

#endif //GRAPH_ALGORITHMS_INL