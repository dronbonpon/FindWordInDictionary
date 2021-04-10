#include "../include/error.h"

#include <unordered_map>
#include <string>

const std::unordered_map<ErrorCode, std::string> errorsMap =
{
    { ErrorCode::cantOpenConfigFile, "Can't open config file" },
    { ErrorCode::cantOpenDict, "Can't open dictionary file" },
    { ErrorCode::cantFindLogLevel, "Can't find logger leve in config file" },
};

std::string GetErrorMessage( ErrorCode code )
{
    return errorsMap.at( code );
}