#pragma once

#include "paginator.h"
#include "singleton.h"
#include "error.h"

#include <vector>
#include <string>
#include <mutex>
#include <optional>

// Синглтон-класс менеджера словаря
class DictionaryUtils : public Singleton<DictionaryUtils>
{
    std::vector<std::string> words;
    mutable std::mutex m;
    friend DictionaryUtils& Singleton::GetInstance();

public:
    // Инициализация словаря
    std::optional<ErrorCode> Initialize( const std::string& dictFileName, 
                                         const std::string& dictFilePath );

    // Обработка одного запроса
    // findAll - true, в случае, если ищем по последовательным символам
    // false - ищем по подстрокам
    // Выполняется, используя то количество потоков, которое указано в конфиге
    void HandleRequest( std::vector<std::string>& result, 
                        std::string& word, bool findAll );
private:

    // static-обертка функции однопоточного обработчика для создания объекта std::thread
    static void HandleRequestSingleCoreWrapper( std::vector<std::string>& result, 
                                                std::vector<std::string>&& words,
                                                std::string& word, bool findAll,
                                                DictionaryUtils* self );

    // Однопоточная функция-обработчик 
    void HandleRequestSingleCore( std::vector<std::string>& result, 
                                  std::vector<std::string>&& words,
                                  std::string& word, bool findAll );

    DictionaryUtils() = default;
};