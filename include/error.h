#pragma once

#include <unordered_map>
#include <string>
#include <optional>


enum class ErrorCode : std::int8_t
{
    cantOpenConfigFile = 1,
    cantOpenDict = 2,
    cantFindLogLevel = 3,
};

std::string GetErrorMessage( ErrorCode code );

void LogError( ErrorCode code, const std::string& file, int line );
