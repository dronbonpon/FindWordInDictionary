#pragma once

#include <vector>
#include <string>

namespace utils
{

    void Split( std::vector<std::string>& result, const std::string& str, 
                const std::string& delimiter );

    bool IsSubSequence( std::string& sequence, std::string& subsequence );

    void VectorToString( const std::vector<std::string>& data,
                         std::string& result, int wordsInLine, 
                         const std::string& delimiter = ", " );

} // namespace utils