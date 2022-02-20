#ifndef GRAPH_GRAPH_INL
#define GRAPH_GRAPH_INL

#include "graph.h"
template<typename Type>
Graph<Type>::Graph(const MatrixType &type, const std::vector<std::vector<int>> &matrix, const std::vector<Type> &vertices) {
    int verticesCounter = matrix.size();
    if (verticesCounter!=vertices.size()){
        throw std::runtime_error("Insufficient number of vertex names!");
    }
    for(int i=0; i<verticesCounter; ++i){
        for(int j=0; j<verticesCounter; ++j){
            if (i!=j && vertices[i]==vertices[j]){
                throw std::runtime_error("Some vertex is duplicated!");
            }
        }
    }

    m_vertices.resize(verticesCounter);
    for(int i=0; i<verticesCounter; ++i){
        m_vertices[i]=i;
    }
    for(int i=0; i<verticesCounter; ++i){
        m_to_names[i]=vertices[i];
        m_to_numbers[vertices[i]]=i;
    }

    if (type == MatrixType::ADJACENCY){
        for (int i=0; i < verticesCounter; ++i){
            if (matrix[i].size() != verticesCounter){
                throw std::runtime_error("The adjacency matrix must be square!");
            }
            for(int j=0; j < verticesCounter; ++j){
                if (!(matrix[i][j] == 0 || matrix[i][j] == 1)){
                    throw std::runtime_error("The adjacency matrix must only contain 0 or 1.");
                }
            }
        }
        m_adjacency_matrix=matrix;
    }
    else if(type == MatrixType::INCIDENCE){
        int edgesCounter = matrix[0].size();
        for(int i=0; i < verticesCounter; ++i){
            if(matrix[i].size() != edgesCounter){
                throw std::runtime_error("The incidence matrix must be rectangular!");
            }
            for(int j=0; j < edgesCounter; ++j){
                if (!(matrix[i][j] == 0 || matrix[i][j] == 1 || matrix[i][j] == -1 || matrix[i][j]==2)){
                    throw std::runtime_error("The incidence matrix must only contain -1, 1, 0 or 2.");
                }
            }
        }
        m_adjacency_matrix.resize(verticesCounter);
        for(int i=0; i < verticesCounter; ++i){
            m_adjacency_matrix[i].resize(verticesCounter);
        }
        for(int j=0; j < edgesCounter; ++j){

        }
    }
    MakeSetRepresentation();
    MakeListRepresentation();
}

template<typename Type>
Graph<Type>::Graph(const std::vector<Type> &vertices, const std::vector<std::pair<Type,Type>> &edges) {
    int edgesCounter = edges.size(), verticesCounter=vertices.size();

    for(int i=0; i<verticesCounter; ++i){
        for(int j=0; j<verticesCounter; ++j){
            if (i!=j && vertices[i]==vertices[j]){
                throw std::runtime_error("Some vertex is duplicated!");
            }
        }
    }

    for(int i=0; i<edgesCounter; ++i){
        std::pair<bool,bool> check;
        for(int j=0; j<verticesCounter; ++j){
            if (vertices[j]==edges[i].first){
                check.first=true;
            }
            if (vertices[j]==edges[i].second){
                check.second=true;
            }
        }
        if(!check.first || !check.second){
            throw std::runtime_error("Some edge contains a non-existent vertex!");
        }
        for(int j=0; j<edgesCounter; ++j){
            if (i!=j && edges[i]==edges[j]){
                throw std::runtime_error("Some edge is duplicated!");
            }
        }
    }

    for(int i=0; i<verticesCounter; ++i){
        m_to_names[i]=vertices[i];
        m_to_numbers[vertices[i]]=i;
    }

    m_vertices.resize(verticesCounter);
    for(int i=0; i<verticesCounter; ++i){
        m_vertices[i]=i;
    }
    for(int i=0; i<edgesCounter; ++i){
        m_edges.push_back({m_to_numbers[edges[i].first], m_to_numbers[edges[i].second]});
    }

    m_adjacency_matrix.resize(verticesCounter);
    for(int i=0; i<verticesCounter; ++i){
        m_adjacency_matrix[i].resize(verticesCounter);
    }
    for(int i=0; i<edgesCounter; ++i){
        m_adjacency_matrix[m_to_numbers[edges[i].first]][m_to_numbers[edges[i].second]]=1;
    }
    MakeListRepresentation();
}


template<typename Type>
Graph<Type>::Graph(const AdjacencyList &type, const std::vector<std::pair<Type,std::vector<Type>>> &adjacencyList) {
    int verticesCounter = adjacencyList.size();
    for(int i=0; i<verticesCounter; ++i){
        m_to_names[i]=adjacencyList[i].first;
        m_to_numbers[adjacencyList[i].first]=i;
        m_vertices.push_back(i);
        for(int j=0; j<verticesCounter; ++j){
            if (i!=j && adjacencyList[i].first==adjacencyList[j].first){
                throw std::runtime_error("Some vertex is duplicated!");
            }
        }
    }
    for(int i=0; i<verticesCounter; ++i){
        int adjacentVertices=adjacencyList[i].second.size();
        for(int j=0; j<adjacentVertices; ++j){
            bool find = false;
            for(int k=0; k<verticesCounter; ++k){
                if(adjacencyList[i].second[j] == m_to_names[m_vertices[k]]){
                    find = true;
                }
            }
            if (!find){
                throw std::runtime_error("There is a nonexistent vertex in the adjacency list!");
            }
        }
        for(int j=0; j<adjacentVertices; ++j){
            for(int k=0; k<adjacentVertices; ++k){
                if(j!=k && adjacencyList[i].second[j]==adjacencyList[i].second[k]){
                    throw std::runtime_error("Adjacent vertices are duplicated!");
                }
            }
        }
    }
    m_adjacency_matrix.resize(verticesCounter);
    for(int i=0; i < verticesCounter; ++i){
        m_adjacency_matrix[i].resize(verticesCounter);
    }
    for(int i=0; i<verticesCounter; ++i){
        int adjacentVertices=adjacencyList[i].second.size();
        for(int j=0; j<adjacentVertices; ++j){
            m_adjacency_matrix[i][m_to_numbers[adjacencyList[i].second[j]]]=1;
        }
    }
    m_adjacency_list.resize(verticesCounter);
    for(int i=0; i<verticesCounter; ++i){
        int adjacentVertices=adjacencyList[i].second.size();
        for(int j=0; j<adjacentVertices; ++j){
            m_adjacency_list[i].push_back(m_to_numbers[adjacencyList[i].second[j]]);
        }
    }
    MakeSetRepresentation();
}


template<typename Type>
std::string Graph<Type>::Graph::PrintAdjacencyMatrix() const{
    int size = m_adjacency_matrix.size();
    std::string output="";
    output += "Graph adjacency matrix:\n";

    for (int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            output += std::to_string(m_adjacency_matrix[i][j]);
            output += " ";
        }
            output += "\n";

    }
    return output;
}

template<typename Type>
std::string Graph<Type>::Graph::PrintIncidenceMatrix() const{
    int size = m_adjacency_matrix.size();
    std::string output="";
    output+="Graph incidence matrix:";
    output+="\n";
    for (int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            for (int k=j+1; k<size; ++k){
                if (m_adjacency_matrix[j][k] == 1 && (i == j or i == k)){
                    output+="1 ";
                }else if (m_adjacency_matrix[j][k] == 1){
                    output+="0 ";
                }
            }
        }
            output += "\n";
    }
    return output;
}

template<typename Type>
void Graph<Type>::Graph::MakeSetRepresentation() {
    int verticesCounter = m_vertices.size();
    for(int i=0; i < verticesCounter; ++i){
        for(int j=0; j < verticesCounter; ++j){
            if (m_adjacency_matrix[i][j] == 1){
                m_edges.push_back({i,j});
            }
        }
    }
}

template<typename Type>
std::string Graph<Type>::Graph::PrintSets() const{
    int verticesCounter = m_vertices.size(), edgesCounter = m_edges.size();
    std::string output;
    output = "Graph set of " + std::to_string(verticesCounter)+" vertices and " +
            std::to_string(edgesCounter)+" edges:\n"+"V = {";
    for(int i=0; i<verticesCounter; ++i){
        if (i==verticesCounter-1) {
            output+=m_to_names.at(m_vertices[i]);
        }else{
            output += m_to_names.at(m_vertices[i]);
            output += ", ";
        }
    }
    output+="};\nE = {";
    for(int i=0; i<edgesCounter; ++i){
        if (i==edgesCounter-1) {
            output+="(";
            output+=m_to_names.at(m_edges[i].first);
            output+=", ";
            output+=m_to_names.at(m_edges[i].second);
            output+=")";
        }else{
            output+="(";
            output+=m_to_names.at(m_edges[i].first);
            output+=", ";
            output+=m_to_names.at(m_edges[i].second);
            output+="), ";
        }
    }
    output += "};";
    return output;
}


template<typename Type>
void Graph<Type>::Graph::MakeListRepresentation() {
    int verticesCounter = m_adjacency_matrix.size();
    m_adjacency_list.resize(verticesCounter);
    for(int i=0; i<verticesCounter; ++i){
        for(int j=0; j<verticesCounter; ++j){
            if(m_adjacency_matrix[i][j]){
                m_adjacency_list[i].push_back(j);
            }
        }
    }
}


template<typename Type>
std::string Graph<Type>::Graph::PrintAdjacencyList() const{
    std::string output="Graph adjacency list:\n";
    int verticesCounter = m_adjacency_matrix.size();
    for(int i=0; i<verticesCounter; ++i){
        output+=m_to_names.at(i);
        output+=": ";
        int adjacentVertices = m_adjacency_list[i].size();
        for(int j=0; j<adjacentVertices; ++j){
            if (j==adjacentVertices-1){
                output+=m_to_names.at(m_adjacency_list[i][j]);
            }else {
                output+=m_to_names.at(m_adjacency_list[i][j]);
                output+=", ";
            }
        }
        output+="\n";
    }
    return output;
}

template<typename Type>
const Graph<Type> &Graph<Type>::Graph::Rename(const Type &name, const Type &rename){
    if(m_to_numbers.find(name)!=m_to_numbers.end()){
        if(m_to_numbers.find(rename)!=m_to_numbers.end()){
            std::cout << "There is already a vertex with name " << rename << std::endl;
        }
        else{
            int number = m_to_numbers[name];
            m_to_names[number]=rename;
            m_to_numbers.erase(name);
            m_to_numbers[rename] = number;
        }
    }
    else{
        std::cout << "There is no vertex with name " << name << std::endl;
    }
    return *this;
}

#endif //GRAPH_GRAPH_INL
