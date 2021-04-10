#pragma once

#include "singleton.h"
#include "error.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <optional>

class ConfigManager : public Singleton<ConfigManager>
{
    friend ConfigManager& Singleton::GetInstance();
    std::unordered_map<std::string, std::string> data;

public:
    std::optional<ErrorCode> Initialize( const std::string& configPath );

    std::string GetDictionaryPath();
    std::string GetDictionaryName();

    int GetMaxWordsInLine();
    int GetMaxWordsPerWindow();

    int GetThreadsNum();

    int GetLogLevel();

private:
    ConfigManager() = default;
};