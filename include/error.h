#pragma once

#include <string>

// Возможные коды ошибок
enum class ErrorCode : std::int8_t
{
    cantOpenConfigFile = 1,
    cantOpenDict = 2,
    cantFindLogLevel = 3,
};

// Получение сообщения об ошибке по ее коду
std::string GetErrorMessage( ErrorCode code );
