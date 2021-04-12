#include "../include/initialize_dict.h"
#include "../include/error.h"
#include "../include/logger.h"

#include <iterator>
#include <fstream>
#include <string>

std::variant<std::string, ErrorCode> InitializeDict( const std::string& dictFileName, 
                                                     const std::string& dictFilePath )
{
    std::variant<std::string, ErrorCode> result;
    
    std::ifstream fileStream( dictFilePath + dictFileName );

    if ( !fileStream.is_open() )
    {
        result = ErrorCode::cantOpenDict;
        return result;
    }

    std::string fileData( ( std::istreambuf_iterator<char>( fileStream ) ),
                            std::istreambuf_iterator<char>() );
    
    if ( fileData.empty() )
    {
        result = ErrorCode::cantOpenDict;
        return result;
    }

    result = fileData;
    return result;
}                                                       
