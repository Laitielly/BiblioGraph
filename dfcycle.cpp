#include"clique.h"

CyclicityResult GreedMaxClique::dfs(int vertex, bool *used, int parent = -1)
{
    used[vertex] = true;
    for (auto neighbor : m_adjacency_list[vertex])
    {
        if (!used[neighbor])
            dfs(neighbor, used,vertex);
        else if(neighbor != parent)
        {
            return CyclicityResult::HasCycle;
        }
    }

    return CyclicityResult::NoneCycle;
}

CyclicityResult GreedMaxClique::Cyclicity()
{
    size_t size = m_adjacency_matrix.size();
    bool used[size];

    return dfs(0, used);
}

