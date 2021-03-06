#ifndef PROJECT_C___GRAPH_TIMER_H
#define PROJECT_C___GRAPH_TIMER_H

#include <iostream>
#include <chrono>

class Timer
{
private:

    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;
    double TimeLimit = 10;
    double eps = 0.0001;

public:
    void StartTimer();

    double elapsed() const;

    bool check() const;
};

#endif //PROJECT_C___GRAPH_TIMER_H
