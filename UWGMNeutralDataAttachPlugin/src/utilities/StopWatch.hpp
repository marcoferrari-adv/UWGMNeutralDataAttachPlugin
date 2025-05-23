#pragma once

#include <chrono>
#include <string>

class StopWatch
{
public:
    StopWatch();

    void start();
    void stop();
    void reset();

    double elapsedMilliseconds() const;
    double elapsedSeconds() const;
    std::string elapsedAsString() const;

private:
    using Clock = std::chrono::high_resolution_clock;
    Clock::time_point m_startTime;
    Clock::time_point m_endTime;
    bool m_running;
};