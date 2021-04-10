#include "../include/logger.h"
#include "../include/config.h"
#include "../include/error.h"

#include <iostream>
#include <optional>
#include <stdexcept>

void Logger::Initialize()
{
    logLevel = static_cast<LogLevel>( ConfigManager::GetInstance().GetLogLevel() );
}

void Logger::LogError( const std::string& message ) const
{
    if ( logLevel == LogLevel::debug ||
         logLevel == LogLevel::error )
    {
        std::cout << "[Error]: " << message << std::endl;
    }
}

void Logger::LogInfo( const std::string& message ) const
{
    if ( logLevel == LogLevel::debug ||
         logLevel == LogLevel::info )
    {
        std::cout << "[Info]: " << message << std::endl;
    }
}

void LogError( const std::string& message )
{
    Logger::GetInstance().LogError( message );
}

void LogInfo( const std::string& message )
{
    Logger::GetInstance().LogInfo( message );
}