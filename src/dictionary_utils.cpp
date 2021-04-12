#include "../include/dictionary_utils.h"
#include "../include/thread_RAII.h"
#include "../include/utils.h"
#include "../include/initialize_dict.h"
#include "../include/config.h"

#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <variant>

std::optional<ErrorCode> DictionaryUtils::Initialize( const std::string& dictFileName, const std::string& dictFilePath )
{ 
    std::variant<std::string, ErrorCode> initializationResult = InitializeDict( dictFileName, dictFilePath );
      
    if ( std::holds_alternative<ErrorCode>( initializationResult ) )
    {
        std::optional<ErrorCode> error = std::get<ErrorCode>( initializationResult );
        return error;
    }

    std::string dictFile = std::get<std::string>( initializationResult );

    utils::Split( words, dictFile, "\n" );
    
    return std::nullopt;
}

void DictionaryUtils::HandleRequest( std::vector<std::string>& result, 
                                     const std::string& word, bool findSubseq ) const
{
    std::vector<ThreadRAII> threads;

    int threadsNum = ConfigManager::GetInstance().GetThreadsNum();
    auto paginatedWords = Paginate( words, words.size()/threadsNum + 1 );

    for ( auto& dictPart : paginatedWords )
    {
        std::vector<std::string> words = { dictPart.begin(), dictPart.end() };
        ThreadRAII oneThread( std::thread( HandleRequestSingleCoreWrapper, std::ref( result ), 
                                           std::move( words ), std::cref( word ), findSubseq, this ), 
                                           ThreadRAII::DtorAction::join );
        
        threads.emplace_back( std::move( oneThread ) );
    }
}

void DictionaryUtils::HandleRequestSingleCoreWrapper( std::vector<std::string>& result, 
                                                      std::vector<std::string>&& words,
                                                      const std::string& word, bool findSubseq,
                                                      const DictionaryUtils* self )
{
    self->HandleRequestSingleCore( result, std::move( words ), word, findSubseq );
}

void DictionaryUtils::HandleRequestSingleCore( std::vector<std::string>& result, 
                                               std::vector<std::string>&& words,
                                               const std::string& word, bool findSubseq ) const
{
    for ( auto& a : words )
    {
        if ( ( findSubseq && utils::IsSubSequence( a, word ) ) || 
             ( !findSubseq && a.find( word ) != std::string::npos )  )
        {
            std::lock_guard<std::mutex> lock( m );
            result.push_back( a );
        }
    }
}