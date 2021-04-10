#pragma once

#include <vector>
#include <string>

namespace utils
{
    // Разделить строку по сепаратору delimiter в вектор
    void Split( std::vector<std::string>& result, const std::string& str, 
                const std::string& delimiter );

    // Проверка на то, что строка является подпоследовательностью другой строки
    bool IsSubSequence( std::string& sequence, std::string& subsequence );

    // Преобразовать вектор в строку с заданным количеством слов в строке и разделителем delimiter
    void VectorToString( const std::vector<std::string>& data,
                         std::string& result, int wordsInLine, 
                         const std::string& delimiter = ", " );

} // namespace utils