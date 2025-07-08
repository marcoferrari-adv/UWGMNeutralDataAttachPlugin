#pragma once

#include <plog/Logger.h>
#include <plog/Log.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include <memory>


class Logger
{
public:
    
    static Logger& get()
    {
        static Logger instance;
        return instance;
    }

    void warn(const std::string& msg)
    { 
        log(plog::Severity::warning, msg);    
    }

    void debug(const std::string& msg)
    {
        log(plog::Severity::debug, msg);
    }

    void error(const std::string& msg)
    {
        log(plog::Severity::error, msg);
    }

private:
    std::unique_ptr<plog::Logger<0>> m_Logger;

    Logger()
    {
        const char* logFile = std::getenv("NEUTRAL_DATA_LOG_FILE");
        const char* logLevel = std::getenv("NEUTRAL_DATA_LOG_LEVEL");

        if (logFile == nullptr || strlen(logFile) < 1 || logLevel == nullptr || strlen(logLevel) < 1)
           return;

        plog::Severity level = plog::Severity::none;
        if (strcmp(logLevel,"debug") == 0) level = plog::Severity::debug;
        else if (strcmp(logLevel,"warn") == 0) level = plog::Severity::warning;
        else if (strcmp(logLevel,"error") == 0) level = plog::Severity::error;

        static auto appender = std::make_shared<plog::RollingFileAppender<plog::TxtFormatter>>(logFile, 8 * 1024 * 1024, 7);
        m_Logger = std::make_unique<plog::Logger<0>>(level);
        m_Logger->addAppender(appender.get());
    }

    void log(plog::Severity severity, const std::string& msg)
    {
        if (m_Logger == nullptr)
            return;
        plog::Record record(severity, __FUNCTION__, __LINE__, __FILE__, nullptr, 0);
        record << msg;
        m_Logger->write(record);
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};