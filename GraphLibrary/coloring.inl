#ifndef GRAPH_COLORING_INL
#define GRAPH_COLORING_INL
#include "graph.h"

template<typename Type>
std::vector<int> Graph<Type>::OptimalColoring_() const {
    size_t size = m_adjacency_matrix.size();
    std::vector<int> result(size,-1);
    std::vector<bool> available(size, false);
    int j = 0;

    result[0]  = 0;
    for (int i = 1; i < size; i++)
    {
        for (auto l : m_adjacency_list[i])
        {
            if (result[l] != -1)
            {
                available[result[l]] = true;
            }
        }

        for (j = 0; j < size; j++)
        {
            if (!available[j])
            {
                break;
            }
        }

        result[i] = j;
        j = 0;

        for (auto l : m_adjacency_list[i])
        {
            if (result[l] != -1)
            {
                available[result[l]] = false;
            }
        }
    }

    return result;
}

template<typename Type>
bool Graph<Type>::IsBipartite_(std::vector<int> &color) const {
    size_t size = m_adjacency_matrix.size();

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
    size_t size = m_adjacency_matrix.size();
    std::vector<int> color(size,-1);

    if (IsBipartite_(color))
    {
        buffer << "Это граф двудольный. Он делится на 2 части:" << std::endl << "1. ";

        std::pair<std::vector<int>, std::vector<int>> bipar;
        for(int i = 0; i < size; ++i)
        {
            if(!color[i])
            {
                bipar.first.push_back(i);
                continue;
            }

            bipar.second.push_back(i);
        }

        size = bipar.first.size();
        buffer << m_to_names.at(bipar.first[0]);
        for(int i = 1; i < size; ++i)
        {
            buffer << ", " << m_to_names.at(bipar.first[i]);
        }
        buffer  << std::endl << "2. " << m_to_names.at(bipar.second[0]);

        size = bipar.second.size();
        for(int i = 1; i < size; ++i)
        {
            buffer << ", " << m_to_names.at(bipar.second[i]);
        }
        buffer  << std::endl;
    } else {
        buffer << "Этот граф не двудольный." << std::endl;
    }

    return buffer.str();
}

template<typename Type>
std::string Graph<Type>::OptimalColoring() const {
    std::stringstream buffer;
    size_t size = m_adjacency_matrix.size();
    std::vector<int> color(size,-1);

    if (IsBipartite_(color))
    {
        buffer << "Этот граф двудольный. Его оптимальная раскраска содержит 2 цвета:" << std::endl << "1. ";

        std::pair<std::vector<int>, std::vector<int>> bipar;
        for(int i = 0; i < size; ++i)
        {
            if(!color[i])
            {
                bipar.first.push_back(i);
                continue;
            }

            bipar.second.push_back(i);
        }

        size = bipar.first.size();
        buffer << m_to_names.at(bipar.first[0]);
        for(int i = 1; i < size; ++i)
        {
            buffer << ", " << m_to_names.at(bipar.first[i]);
        }
        buffer  << std::endl << "2. " << m_to_names.at(bipar.second[0]);

        size = bipar.second.size();
        for(int i = 1; i < size; ++i)
        {
            buffer << ", " << m_to_names.at(bipar.second[i]);
        }
        buffer  << std::endl;
    } else {
        auto result = OptimalColoring_();
        size_t size = result.size(), sizel = 0;
        std::vector<std::vector<int>> res;
        std::vector<int> vec;
        std::vector<bool> used(size, false);

        for (auto i : result)
        {
            if (used[i])
            {
                continue;
            }
            for(int j = 0; j < size; ++j)
            {

                if(result[j] == i)
                {
                    vec.push_back(j);
                }
            }

            res.push_back(vec);
            vec.clear();
            used[i] = true;
        }

        size = res.size();
        buffer << "Всего цветов раскраски: " << size << "." << std::endl;
        for(int i = 0; i < size; ++i)
        {
            sizel = res[i].size();
            buffer << "Вы можете расскрасить следующие вершины, используя один цвет (" << i << "): " << m_to_names.at(res[i][0]);
            for(int j = 1; j < sizel; ++j)
            {
                buffer << ", " << m_to_names.at(res[i][j]);
            }
            buffer << std::endl;
        }
    }

    return buffer.str();
}

#endif //GRAPH_COLORING_INL
