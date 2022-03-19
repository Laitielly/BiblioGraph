#ifndef GRAPH_COLORING_INL
#define GRAPH_COLORING_INL
#include "graph.h"

template<typename Type>
bool Graph<Type>::IsBipartite_() const {
    size_t size = m_adjacency_matrix.size();
    std::vector<int> color(size, -1);

    std::queue<std::pair<int, int>> q;

    for (int i = 0; i < size; i++)
    {
        if (color[i] == -1)
        {
            q.push({ i, 0 });
            color[i] = 0;

            while (!q.empty())
            {
                std::pair<int, int> p = q.front();
                q.pop();
                int v = p.first;
                int c = p.second;

                for (int j : m_adjacency_list[v])
                {
                    if (color[j] == c)
                    {
                        return false;}


                    if (color[j] == -1)
                    {
                        color[j] = (c) ? 0 : 1;
                        q.push({ j, color[j] });
                    }
                }
            }
        }
    }

    return true;
}

template<typename Type>
std::string Graph<Type>::IsBipartite() const {
    std::stringstream buffer;

    if (IsBipartite_())
    {
        buffer << "This graph is bipartite!" << std::endl;
    } else {
        buffer << "This graph is not bipartite!" << std::endl;
    }

    return buffer.str();
}

#endif //GRAPH_COLORING_INL