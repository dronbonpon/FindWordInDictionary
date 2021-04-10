#pragma once

#include "paginator.h"
#include "singleton.h"
#include "error.h"

#include <vector>
#include <string>
#include <mutex>
#include <optional>

class DictionaryUtils : public Singleton<DictionaryUtils>
{
    std::vector<std::string> words;
    mutable std::mutex m;
    friend DictionaryUtils& Singleton::GetInstance();

public:

    std::optional<ErrorCode> Initialize( const std::string& dictFileName, 
                                         const std::string& dictFilePath );

    void HandleRequest( std::vector<std::string>& result, 
                        std::string& word, bool findAll );
private:

    static void HandleRequestSingleCoreWrapper( std::vector<std::string>& result, 
                                                std::vector<std::string>&& words,
                                                std::string& word, bool findAll,
                                                DictionaryUtils* self );

    void HandleRequestSingleCore( std::vector<std::string>& result, 
                                  std::vector<std::string>&& words,
                                  std::string& word, bool findAll );

    DictionaryUtils() = default;
};