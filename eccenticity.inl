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
    if(m_to_numbers.find(name)!=m_to_numbers.end()){
        std::cout << "The eccentricity of the vertex " << name << " is equal to " << Eccentricity_(m_to_numbers.at(name));
    }
    else{
        std::cout << "There is no vertex with name " << name << std::endl;
    }
}

#endif //GRAPH_ECCENTRICITY_INL
