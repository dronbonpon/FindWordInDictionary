cmake_minimum_required(VERSION 3.5)

project(dictionary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR_PLATFORM x86)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

set(SOURCE_FILES main.cpp error.cpp utils.cpp initialize_dict.cpp dictionary_utils.cpp config.cpp logger.cpp result.cpp)

add_executable(main ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(main ${GTK3_LIBRARIES})

TARGET_LINK_LIBRARIES(main pthread)


