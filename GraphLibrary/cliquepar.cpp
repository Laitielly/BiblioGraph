#include "clique.h"

bool GreedMaxClique::IsClique(const int size)
{
    for (int i = 1; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (!m_adjacency_matrix[store[i]][store[j]])
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<int> GreedMaxClique::ConvertToVector(int n)
{
    std::vector<int> clique(n - 1);

    for (int i = 1; i < n; i++)
    {
        clique[i - 1] = store[i];
    }

    return clique;

}

CliqueControl GreedMaxClique::FindCliques2(const int i, const int l, const int s, size_t size, std::vector<std::vector<int>> &cliques)
{
    for (int j = i + 1; j <= size - (s - l); j++)
    {
        if (degree[j] >= s - 1)
        {
            store[l] = j;

            if (IsClique(l + 1))
            {
                if (l < s)
                {
                    if (this -> check())
                    {
                        return CliqueControl::TimeLimit;
                    }

                    FindCliques2(j, l + 1, s, size, cliques);
                }

                else
                {
                    cliques.push_back(ConvertToVector(l + 1));
                }
            }
        }

        if (this -> check())
        {
            return CliqueControl::TimeLimit;
        }
    }

    if (cliques.empty())
    {
        return CliqueControl::CannotFind;
    }

    return CliqueControl::IsFind;
}

CliqueControl GreedMaxClique::CliqueWithSize(int k)
{
    size_t size = edges.size(), sizemat = m_adjacency_matrix.size();
    store.resize(sizemat);
    degree.resize(sizemat);

    for (int i = 0; i < size; i++) {
        degree[edges[i].first]++;
        degree[edges[i].second]++;
    }

    std::vector<std::vector<int>> cliques;

    this -> StartTimer();
    auto position = FindCliques2(-1, 1, k, sizemat - 1, cliques);

    if (position == CliqueControl::IsFind)
    {
        cliquesizek = cliques;
    }

    return position;
}

