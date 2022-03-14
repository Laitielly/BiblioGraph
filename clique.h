#ifndef PROJECT_C___GRAPH_CLIQUE_H
#define PROJECT_C___GRAPH_CLIQUE_H

#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>
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
    NoneCycle,
    TimeLimit
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

    std::vector<std::vector<int>> cycleparam;

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

    CyclicityResult dfs(const int vertex, bool *used, const int parent);

    CyclicityResult CyclicitySize(const int n);

    void DFS(bool marked[], const int n, const int vert, const int start, std::vector<int> &gap, const class Timer &time);

    void Check(std::vector<int> gap);

    static bool Compare(const std::vector<int>& cycle, const std::vector<int>& gap);

    std::vector<std::vector<int>> TakeSizeCycle();

};

#endif //PROJECT_C___GRAPH_CLIQUE_H
