#include "pch.hpp"

#include "StopWatch.hpp"

#include <sstream>
#include <iomanip>

StopWatch::StopWatch() : m_running(false) {}

void StopWatch::start()
{
    m_startTime = Clock::now();
    m_running = true;
}

void StopWatch::stop()
{
    m_endTime = Clock::now();
    m_running = false;
}

void StopWatch::reset()
{
    m_running = false;
    m_startTime = Clock::now();
    m_endTime = m_startTime;
}

double StopWatch::elapsedMilliseconds() const
{
    auto end = m_running ? Clock::now() : m_endTime;
    return std::chrono::duration<double, std::milli>(end - m_startTime).count();
}

double StopWatch::elapsedSeconds() const
{
    auto end = m_running ? Clock::now() : m_endTime;
    return std::chrono::duration<double>(end - m_startTime).count();
}

const std::string& StopWatch::elapsedAsString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << elapsedSeconds() << "s";
    return oss.str();
}