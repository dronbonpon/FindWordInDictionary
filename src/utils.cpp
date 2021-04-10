#include "../include/utils.h"

#include <vector>
#include <string>
#include <sstream>

namespace utils
{
    void Split( std::vector<std::string>& result, const std::string& str, 
                const std::string& delimiter )
    {
        result.clear();
        std::string::size_type start = 0;
        
        auto pos = str.find_first_of( delimiter, start );
        while( pos != std::string::npos )
        {
            result.emplace_back( str, start, pos - start );
            
            start = pos + 1;
            pos = str.find_first_of( delimiter, start );
        }
        if( start < str.length() )
        {
            result.emplace_back( str, start, str.length() - start );
        }
    }

    bool IsSubSequence( std::string& sequence, std::string& subsequence, 
                        int sequenceSize, int subsequenceSize )
    {
        if ( sequenceSize < subsequenceSize )
        {
            return false;
        }

        if ( subsequenceSize == 0 )
        {
            return true;
        }
        if ( sequenceSize == 0 )
        {
            return false;
        }

        if ( sequence[sequenceSize-1] == subsequence[subsequenceSize-1] )
        {
            return IsSubSequence( sequence, subsequence, sequenceSize - 1, subsequenceSize - 1 );
        }

        return IsSubSequence( sequence, subsequence, sequenceSize - 1, subsequenceSize );
    }

    bool IsSubSequence( std::string& sequence, std::string& subsequence )
    {
        return IsSubSequence( sequence, subsequence, sequence.size(), subsequence.size() );
    }

    void VectorToString( const std::vector<std::string>& data,
                         std::string& result, int wordsInLine, 
                         const std::string& delimiter )
    {
        int wordsInCurrentLine = 0;
        std::ostringstream resultStream;

        for ( const auto& token : data )
        {
            if ( wordsInCurrentLine < wordsInLine )
            {
                resultStream << token << delimiter;
                ++wordsInCurrentLine;
            }
            else
            {
                resultStream << "\n" << token;
                wordsInCurrentLine = 0;
            }
        }
        result = resultStream.str();
    }
} // namespace utils