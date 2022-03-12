#include "clique.h"
#include "Timer.h"

CliqueControl GreedMaxClique::FindClique(std::list<int> &clique)
{
    Timer time;

    size_t size = m_adjacency_matrix.size(), maxcliq = 0;
    std::list<int> maxclique;

    for (int j = 0; j < size; ++j)
    {
        clique.push_back(j);

        for (int i = j + 1; i < size; ++i)
        {
            if (VertexInClique(i, clique))
            {
                if (time.check())
                {
                    return CliqueControl::TimeLimit;
                }

                continue;
            }

            bool isNext = true;
            for (auto iter = clique.begin(); iter != clique.end(); iter++)
            {
                if (m_adjacency_matrix[i][*iter])
                {
                    if (time.check())
                    {
                        return CliqueControl::TimeLimit;
                    }

                    continue;
                } else {
                    isNext = false;
                    break;
                }
            }

            if (isNext) {
                clique.push_back(i);
            }

            if (time.check())
            {
                return CliqueControl::TimeLimit;
            }
        }

        if (maxcliq < clique.size())
        {
            maxclique.clear();
            maxclique = clique;
            maxcliq = clique.size();
        }

        clique.clear();
    }

    maxclique.sort();
    clique = maxclique;

    if (clique.size() <= 1)
    {
        return CliqueControl::CannotFind;
    }

    return  CliqueControl::IsFind;
}

bool GreedMaxClique::VertexInClique(const int vertex, const std::list<int>& clique)
{
    for (int iter : clique)
    {
        if (iter == vertex)
        {
            return true;
        }
    }

    return false;
}

CliqueControl GreedMaxClique::Start(const CliqueMethod method, const int k)
{
    if (method == CliqueMethod::MaxClique)
    {
        std::list<int> clique;
        auto status = FindClique(clique);

        if (status == CliqueControl::IsFind)
        {
            maxclique = clique;
        }

        return status;
    }

    else if (method == CliqueMethod::CliqueWithKey)
    {
        return CliqueWithSize(k);
    }

}

void GreedMaxClique::Print()
{

    std::cout << std:: endl << "Cliques size k: " << cliquesizek.size() << std::endl;
    for(int i = 0; i < cliquesizek.size(); ++i)
    {
        for(int j = 0; j < cliquesizek[i].size(); ++j)
        {
            std::cout<<cliquesizek[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

GreedMaxClique::GreedMaxClique(std::vector<std::vector<int>> adjacency_matrix, std::vector<std::pair<int, int>> edg) {
    m_adjacency_matrix = adjacency_matrix;
    edges=edg;
}

std::list<int> GreedMaxClique::TakeMaxClique() {
    return maxclique;
}

std::vector<std::vector<int>> GreedMaxClique::TakeSizeClique() {
    return cliquesizek;
}


