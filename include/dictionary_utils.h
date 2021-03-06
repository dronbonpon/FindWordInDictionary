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
    // findSubseq - true, в случае, если ищем по последовательным символам
    // false - ищем по подстрокам
    // Выполняется, используя то количество потоков, которое указано в конфиге
    void HandleRequest( std::vector<std::string>& result, 
                        const std::string& word, bool findSubseq ) const;
private:

    // static-обертка функции однопоточного обработчика для создания объекта std::thread
    static void HandleRequestSingleCoreWrapper( std::vector<std::string>& result, 
                                                std::vector<std::string>&& words,
                                                const std::string& word, bool findSubseq,
                                                const DictionaryUtils* self );

    // Однопоточная функция-обработчик 
    void HandleRequestSingleCore( std::vector<std::string>& result, 
                                  std::vector<std::string>&& words,
                                  const std::string& word, bool findSubseq ) const;

    DictionaryUtils() = default;
};