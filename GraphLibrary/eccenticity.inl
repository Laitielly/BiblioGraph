#ifndef GRAPH_ECCENTRICITY_INL
#define GRAPH_ECCENTRICITY_INL
#include "graph.h"

template<typename Type>
int Graph<Type>::Eccentricity_(int name) const
{
    std::queue<int> q;
    size_t size = m_adjacency_matrix.size();
    std::vector<int> distance(size, -1);
    int current = 0;

    distance[name] = 0;
    q.push(name);

    while (!q.empty())
    {
        current = q.front();
        q.pop();

        for(auto item : m_adjacency_list[current])
        {
            if (distance[item] == -1)
            {
                distance[item] = distance[current] + 1;
                q.push(item);
            }
        }
    }

    return distance[current];
}

template<typename Type>
std::string Graph<Type>::Eccentricity(const Type &name) const
{
    std::stringstream buffer;

    if(m_to_numbers.find(name)!=m_to_numbers.end()){
        buffer << "The eccentricity of the vertex " << name << " is equal to " << Eccentricity_(m_to_numbers.at(name)) << "." << std::endl;
    }
    else{
        buffer << "There is no vertex with name " << name << "!" << std::endl;
    }

    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::FindDiameter() const {
    std::stringstream buffer;

    size_t size = m_adjacency_matrix.size();
    int exx = 0, parameter = 0;

    for (int i = 0; i < size; ++i){
        parameter = Eccentricity_(i);

        if (parameter > exx)
        {
            exx = parameter;
        }
    }

    buffer << "The diameter of the graph is equal to " << exx << "." << std::endl;
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::FindRadius() const {
    std::stringstream buffer;

    std::pair<int, std::vector<int>> exx = FindRadius_();

    buffer << "The radius of the graph is equal to " << exx.first << "." << std::endl;
    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::FindCentralVertices() const {
    std::stringstream buffer;
    std::pair<int, std::vector<int>> exx = FindRadius_();
    size_t size = exx.second.size();

    buffer << "The central vertices of the graph: ";
    std::list<int> add;

    for(int i = 0; i < size; ++i)
    {
        if (exx.second[i] == exx.first)
        {
            add.push_back(i);
        }
    }

    int i = 0;
    size = add.size();
    for(auto &item : add)
    {
        buffer << m_to_names.at(item);

        if (i != size - 1)
        {
            buffer << ", ";
        }

        ++i;
    }

    buffer << "." << std::endl;

    return buffer.str();
}

template<typename Type>
std::pair<int, std::vector<int>> Graph<Type>::FindRadius_() const {
    size_t size = m_adjacency_matrix.size();
    std::vector<int> ecc;
    int exx = 0, parameter = 0;

    exx = Eccentricity_(0);
    for (int i = 1; i < size; ++i){
        parameter = Eccentricity_(i);
        ecc.push_back(parameter);

        if (parameter < exx)
        {
            exx = parameter;
        }
    }

    return std::pair<int, std::vector<int>>(exx, ecc);
}

#endif //GRAPH_ECCENTRICITY_INL
