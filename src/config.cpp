#include "../include/config.h"
#include "../include/error.h"
#include "../include/utils.h"
#include "../include/logger.h"

#include <fstream>
#include <string>
#include <optional>
#include <vector>

std::optional<ErrorCode> ConfigManager::Initialize( const std::string& configPath )
{
    std::ifstream configStream( configPath );
    if ( !configStream.is_open() )
    {
        std::optional<ErrorCode> error = ErrorCode::cantOpenConfigFile;
        LogError( GetErrorMessage( ErrorCode::cantOpenConfigFile ) );
        return error;
    }

    std::string configStr( ( std::istreambuf_iterator<char>( configStream ) ),
                             std::istreambuf_iterator<char>() );
    if ( configStr.empty() )
    {
        std::optional<ErrorCode> error = ErrorCode::cantOpenConfigFile;
        LogError( GetErrorMessage( ErrorCode::cantOpenConfigFile ) );
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

std::string ConfigManager::GetDictionaryPath() const
{
    if ( data.find( "dictionary.path" ) != data.end() )
    {
        return data.at( "dictionary.path" );
    }
    return "../";
}

std::string ConfigManager::GetDictionaryName() const
{
    if ( data.find( "dictionary.name" ) != data.end() )
    {
        return data.at( "dictionary.name" );
    }
    return "words.txt";
}

int ConfigManager::GetMaxWordsInLine() const
{
    if ( data.find( "words.in.line" ) != data.end() )
    {
        return std::atoi( data.at( "words.in.line" ).c_str() );
    }
    return 6;
}

int ConfigManager::GetThreadsNum() const
{
    if ( data.find( "threads.num" ) != data.end() )
    {
        return std::atoi( data.at( "threads.num" ).c_str() );
    }
    return 2;
}

int ConfigManager::GetLogLevel() const
{
    if ( data.find( "log.level" ) != data.end() )
    {
        return std::atoi( data.at( "log.level" ).c_str() );
    }
    return 1;
}