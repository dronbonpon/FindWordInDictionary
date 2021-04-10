#include "../include/initialize_dict.h"
#include "../include/utils.h"

#include <iterator>
#include <fstream>
#include <iostream>

std::variant<std::string, ErrorCode> InitializeDict( const std::string& dictFileName, 
                                                     const std::string& dictFilePath )
{
    std::variant<std::string, ErrorCode> result;
    
    std::ifstream fileStream( dictFilePath + dictFileName );

    if ( !fileStream.is_open() )
    {
        result = ErrorCode::cantOpenDict;
        LogError( ErrorCode::cantOpenDict, __FILE__, __LINE__ );
        return result;
    }

    std::string fileData( ( std::istreambuf_iterator<char>( fileStream ) ),
                            std::istreambuf_iterator<char>() );
    
    if ( fileData.empty() )
    {
        result = ErrorCode::cantOpenDict;
        LogError( ErrorCode::cantOpenDict, __FILE__, __LINE__ );
        return result;
    }

    result = fileData;
    return result;
}                                                       
