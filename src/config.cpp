#include "../include/config.h"
#include "../include/error.h"
#include "../include/utils.h"

#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <iostream>

std::optional<ErrorCode> ConfigManager::Initialize( const std::string& configPath )
{
    
    std::ifstream configStream( configPath );
    if ( !configStream.is_open() )
    {
        std::optional<ErrorCode> error = ErrorCode::cantOpenConfigFile;
        LogError( ErrorCode::cantOpenConfigFile, __FILE__, __LINE__ );
        return error;
    }

    std::string configStr( ( std::istreambuf_iterator<char>( configStream ) ),
                             std::istreambuf_iterator<char>() );
    if ( configStr.empty() )
    {
        std::optional<ErrorCode> error = ErrorCode::cantOpenConfigFile;
        LogError( ErrorCode::cantOpenConfigFile, __FILE__, __LINE__ );
        return error;
    }

    std::vector<std::string> configVector;
    utils::Split( configVector, configStr, "\n" );

    for ( const auto& line: configVector )
    {
        if ( line.size() > 1 && line[0] != '#' )
        {
            std::vector<std::string> configLine;
            utils::Split( configLine, line, "=" );
            data.insert( std::make_pair( configLine[0], configLine[1] ) );
        }
    }

    return std::nullopt;
}

std::string ConfigManager::GetDictionaryPath()
{
    return data.at( "dictionary.path" );
}

std::string ConfigManager::GetDictionaryName()
{
    return data.at( "dictionary.name" );
}

int ConfigManager::GetMaxWordsInLine()
{
    return std::atoi( data.at( "words.in.line" ).c_str() );
}

int ConfigManager::GetMaxWordsPerWindow()
{
    return std::atoi( data.at( "words.per.window" ).c_str() );
}

int ConfigManager::GetThreadsNum()
{
    return std::atoi( data.at( "threads.num" ).c_str() );
}

int ConfigManager::GetLogLevel()
{
    return std::atoi( data.at( "log.level" ).c_str() );
}