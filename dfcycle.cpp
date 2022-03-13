#include"clique.h"

CyclicityResult GreedMaxClique::dfs(const int vertex, bool used[], const int parent = -1)
{
    used[vertex] = true;
    for (auto neighbor : m_adjacency_list[vertex])
    {
        if (!used[neighbor])
            return dfs(neighbor, used,vertex);
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

bool GreedMaxClique::Compare(const std::vector<int>& cycle, const std::vector<int>& gap)
{
    size_t size = cycle.size();
    for (int i = 0; i < size; ++i)
    {
        if (cycle[i] != gap[i])
        {
            return false;
        }
    }

    return true;
}

void GreedMaxClique::Check(std::vector<int> gap)
{
    std::sort(gap.begin(), gap.end());
    size_t size = cycleparam.size();

    for(int i = 0; i < size; ++i)
    {
        if (Compare(cycleparam[i],gap))
        {
            return;
        }
    }

    cycleparam.push_back(gap);
}

void GreedMaxClique::DFS(bool marked[], const int n, const int vert, const int start, std::vector<int> &gap)
{
    marked[vert] = true;
    gap.push_back(vert);

    if (n == 0)
    {
        marked[vert] = false;
        if (m_adjacency_matrix[vert][start])
        {
            Check(gap);
            gap.erase(gap.end() - 1);
            return;
        } else {
            gap.erase(gap.end() - 1);
            return;
        }
    }

    size_t size = m_adjacency_matrix.size();
    for (int i = 0; i < size; i++)
    {
        if (!marked[i] && m_adjacency_matrix[vert][i])
        {
            DFS(marked, n - 1, i, start, gap);
        }
    }

    marked[vert] = false;
    gap.erase(gap.end()-1);
}

void GreedMaxClique::countCycles(const int n)
{
    size_t size = m_adjacency_matrix.size();
    bool marked[size];
    memset(marked, 0, sizeof(marked));
    std::vector<int> gap;

    for (int i = 0; i < size - (n - 1); i++) {
        DFS(marked, n - 1, i, i, gap);
        marked[i] = true;
        gap.clear();
    }
}

CyclicityResult GreedMaxClique::CyclicitySize(const int n)
{
    countCycles(n);

    if (cycleparam.empty())
    {
        return CyclicityResult::NoneCycle;
    }

    return CyclicityResult::HasCycle;
}

std::vector<std::vector<int>> GreedMaxClique::TakeSizeCycle() {
    return cycleparam;
}

