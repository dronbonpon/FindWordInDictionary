#pragma once

#include "singleton.h"
#include "error.h"

#include <unordered_map>
#include <string>
#include <optional>

// Синглтон-класс менеджера конфигурации приложения
class ConfigManager : public Singleton<ConfigManager>
{
    friend ConfigManager& Singleton::GetInstance();
    std::unordered_map<std::string, std::string> data;

public:
    // Инициализация менеджера конфигурации
    std::optional<ErrorCode> Initialize( const std::string& configPath );

    // Получить путь к словарю
    std::string GetDictionaryPath() const;
    // Получить имя словаря
    std::string GetDictionaryName() const;

    // Получить максимальное количество слов в одной строке
    int GetMaxWordsInLine() const;

    // Получить допустимое число используемых потоков
    int GetThreadsNum() const;

    // Получить уровень логирования
    int GetLogLevel() const;

private:
    ConfigManager() = default;
};