#pragma once

#include "singleton.h"
#include "error.h"

#include <string>
#include <optional>

enum class LogLevel : std::int8_t
{
    debug = 1,
    error = 2,
    info = 3
};

class Logger : public Singleton<Logger>
{
    friend Logger& Singleton::GetInstance();
    LogLevel logLevel = LogLevel::debug;
    Logger() = default;

public:
    std::optional<ErrorCode> Initialize();

    void LogError( const std::string& message ) const;
    void LogInfo( const std::string& message ) const;
};

void LogError( const std::string& message );
void LogInfo( const std::string& message );