#pragma once

#include <string>

namespace result
{
    // Получить результат запроса в виде строки для посимвольного поиска
    void ForSubsequences( std::string& result, 
                          std::string& word );
    
    // Получить результат в виде строки для поиска по подстрокам
    void ForSubstrings( std::string& result, 
                        std::string& word );

} // namespace result