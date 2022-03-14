#include"Timer.h"

Timer::Timer() : m_beg(clock_t::now()) {}

double Timer::elapsed() const
{
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

bool Timer::check() const
{
    if (this->elapsed() - (TimeLimit) > eps)
    {
        return true;
    }

    return false;
}

