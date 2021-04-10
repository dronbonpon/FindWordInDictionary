#pragma once

#include "error.h"

#include <string>
#include <variant>

std::variant<std::string, ErrorCode> InitializeDict( const std::string& dictFileName, 
                                                     const std::string& dictFilePath );