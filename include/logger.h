#pragma once

#include "singleton.h"

#include <string>

// Возможные уровни логирования
enum class LogLevel : std::int8_t
{
    debug = 1,  // Печатаем все сообщения
    error = 2,  // Печатаем только сообщения об ошибках
    info = 3,   // Печатаем только информационные сообщения
};

// Синглтон-класс логгера
class Logger : public Singleton<Logger>
{
    friend Logger& Singleton::GetInstance();
    LogLevel logLevel = LogLevel::debug;
    Logger() = default;

public:
    // Метод инициализации логгера
    void Initialize();

    // Вывести сообщение об ошибке
    void LogError( const std::string& message ) const;
    // Вывести информационное сообщение
    void LogInfo( const std::string& message ) const;
};

// Функции-обертки для уменьшения длины кода вызова методов класса
void LogError( const std::string& message );
void LogInfo( const std::string& message );