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
        buffer << "Граф неориентированный." << std::endl;
        return buffer.str();
    }else{
        buffer << "Граф ориентированный." << std::endl;
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
        buffer << "В графе есть петли." << std::endl;
        return buffer.str();
    }else{
        buffer << "В графе нет петель." << std::endl;
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
    buffer << "В графе "<<directed<<" ориентированных ребер, "<< undirected <<" неориентированных ребер и "<<loop<<" петель."<<std::endl;
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
        buffer << "Степень вершины " << name << " равна " << PrintVertexDegree_(name) << "." << std::endl;
    }else{
        buffer << "Вершины " << name << " нет в графе." << std::endl;
    }
    return buffer.str();
}


template<typename Type>
std::string Graph<Type>::VerticesNumber() const {
    std::stringstream buffer;
    buffer << "В графе " << m_vertices.size() <<" вершин."<<std::endl;
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
        buffer << "Размер максимальной клики равен " << size <<"."<<std::endl;
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
        buffer << "Невозможно найти максимальную клику. Превышено время ожидания." << std::endl;
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
            buffer << "Клики размера " << size << ":" <<std::endl;
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
            buffer << "Не возможно найти клики. Превышено время ожидания." << std::endl;
        } else if (result == CliqueControl::CannotFind) {
            buffer << "Клики размера " << size << " не существуют." << std::endl;
        }
    } else{
        buffer << "Клика размера " << size << " не может быть в графе с " << m_vertices.size() << " вершинами." << std::endl;
    }
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::FindCycles() const {
    std::stringstream buffer;
    GreedMaxClique cycle(m_adjacency_matrix, m_edges, m_adjacency_list);
    CyclicityResult result = cycle.Cyclicity();
    if(result == CyclicityResult::HasCycle){
        buffer << "В графе есть циклы." <<std::endl;
    }else if(result == CyclicityResult::NoneCycle){
        buffer << "В графе нет циклов." << std::endl;
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
            buffer << "Циклы размера " << n <<":" << std::endl;
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
            buffer << "В этом графе нет циклов размера " << n << "."<< std::endl;
        } else if (result == CyclicityResult::TimeLimit) {
            buffer << "Не возможно найти циклы размера " << n << ". Превышено время ожидания." << std::endl;
        }
    }else{
        if (m_adjacency_matrix.size()<3){
            buffer << "Не может быть циклов в графе с " << m_adjacency_matrix.size() <<" вершинами." << std::endl;
        }else if(m_adjacency_matrix.size()==3){
            buffer << "Циклы в графе на 3 вершины могут иметь только длину 3." << std::endl;
        }else {
            buffer << "Циклы в графе с " << m_adjacency_matrix.size() << " вершинами могут иметь длину от 3 до "
                   << m_adjacency_matrix.size() << "." << std::endl;
        }
    }
    return buffer.str();
}




#endif //GRAPH_ALGORITHMS_INL