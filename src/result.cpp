#include "../include/result.h"
#include "../include/logger.h"
#include "../include/config.h"
#include "../include/utils.h"
#include "../include/dictionary_utils.h"

#include <sstream>

namespace result
{
    void ForSubsequences( std::string& result, 
                          std::string& word )
    {

        std::vector<std::string> matches;
        DictionaryUtils::GetInstance().HandleRequest( matches, word, true );

        std::ostringstream logInfoMessage;
        logInfoMessage << "For the word "
                       <<  "\"" << word << "\""
                       << " there are "
                       << matches.size()
                       << " words for which " 
                       << "\"" << word << "\""
                       << " is a subsequence";

        LogInfo( logInfoMessage.str() );

        int maxWordsInLine = ConfigManager::GetInstance().GetMaxWordsInLine();

        if ( matches.empty() )
        {
            result = "Can't find any";
        }
        else
        {
            utils::VectorToString( matches, result, maxWordsInLine );
            result = result.substr( 0, result.size() - 2 );
        }
    }

    void ForSubstrings( std::string& result, 
                        std::string& word )
    {

        std::vector<std::string> matches;
        DictionaryUtils::GetInstance().HandleRequest( matches, word, false );

        std::ostringstream logInfoMessage;
        logInfoMessage << "For the word "
                       << "\"" << word << "\""
                       << " there are "
                       << matches.size()
                       << " words for which " 
                       << "\"" << word << "\""
                       << " is a substring";

        LogInfo( logInfoMessage.str() );

        int maxWordsInLine = ConfigManager::GetInstance().GetMaxWordsInLine();

        if ( matches.empty() )
        {
            result = "Can't find any";
        }
        else
        {
            utils::VectorToString( matches, result, maxWordsInLine );
            result = result.substr( 0, result.size() - 2 );
        }
    }

}