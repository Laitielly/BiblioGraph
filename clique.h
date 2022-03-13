#ifndef PROJECT_C___GRAPH_CLIQUE_H
#define PROJECT_C___GRAPH_CLIQUE_H

#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <cmath>
#include "timer.h"

enum class CliqueControl {
    TimeLimit,
    CannotFind,
    IsFind
};

enum class CliqueMethod {
    MaxClique,
    CliqueWithKey
};

enum class CyclicityResult {
    HasCycle,
    NoneCycle
};

class GreedMaxClique {
private:
    std::vector<std::vector<int>> m_adjacency_matrix;
    std::vector<std::pair<int,int>> edges;
    std::vector<std::vector<int>> m_adjacency_list;

    std::vector<int> degree;
    std::vector<int> store;

    std::list<int> maxclique;
    std::vector<std::vector<int>> cliquesizek;

public:
    GreedMaxClique(std::vector<std::vector<int>> adjacency_matrix, std::vector<std::pair<int,int>> edg, std::vector<std::vector<int>> adjacency_list);
    friend class Timer;

    CliqueControl Start(const CliqueMethod method, const int k);

    CliqueControl FindClique(std::list<int> &clique);

    static bool VertexInClique(const int vertex, const std::list<int>& clique);

    CliqueControl CliqueWithSize(const int k);

    bool IsClique(const int size);

    std::vector<int> ConvertToVector(const int n);

    CliqueControl FindCliques2(const int i, const int l, const int s, size_t size, std::vector<std::vector<int>> &cliques, Timer &time);

    std::list<int> TakeMaxClique();

    std::vector<std::vector<int>> TakeSizeClique();

    CyclicityResult Cyclicity();

    CyclicityResult dfs(int vertex, bool *used, int parent);

};

#endif //PROJECT_C___GRAPH_CLIQUE_H
