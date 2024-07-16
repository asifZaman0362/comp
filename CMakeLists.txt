cmake_minimum_required(VERSION 3.5)
project(computer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(inc)

set(SOURCE_FILES src/main.cc)
set(HEADER_FILES inc/option.hpp inc/result.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
