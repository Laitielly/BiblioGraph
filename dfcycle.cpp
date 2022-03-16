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

void GreedMaxClique::Check(const std::vector<int> &gap, std::vector<std::vector<int>> &copymain)
{
    std::vector<int> copygap = gap;
    std::sort(copygap.begin(), copygap.end());
    size_t size = cycleparam.size();

    for(int i = 0; i < size; ++i)
    {
        if (Compare(copymain[i],copygap))
        {
            return;
        }
    }

    copymain.push_back(copygap);
    cycleparam.push_back(gap);
}

void GreedMaxClique::DFS(bool marked[], const int n, const int vert, const int start, std::vector<int> &gap, std::vector<std::vector<int>> &copymain)
{
    marked[vert] = true;
    gap.push_back(vert);

    if (this -> check())
    {
        return;
    }

    if (n == 0)
    {
        marked[vert] = false;
        if (m_adjacency_matrix[vert][start])
        {
            Check(gap, copymain);
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
            DFS(marked, n - 1, i, start, gap, copymain);
        }

        if (this -> check())
        {
            return;
        }
    }

    marked[vert] = false;
    gap.erase(gap.end()-1);

    if (this -> check())
    {
        return;
    }
}

CyclicityResult GreedMaxClique::CyclicitySize(const int n)
{
    this -> StartTimer();

    size_t size = m_adjacency_matrix.size();
    bool marked[size];
    memset(marked, 0, sizeof(marked));
    std::vector<int> gap;
    std::vector<std::vector<int>> copymain;

    for (int i = 0; i < size - (n - 1); i++) {
        DFS(marked, n - 1, i, i, gap, copymain);
        marked[i] = true;
        gap.clear();

        if (this -> check())
        {
            return CyclicityResult::TimeLimit;
        }
    }

    if (cycleparam.empty())
    {
        return CyclicityResult::NoneCycle;
    }
    return CyclicityResult::HasCycle;
}

std::vector<std::vector<int>> GreedMaxClique::TakeSizeCycle()
{
    return cycleparam;
}

