cmake_minimum_required(VERSION 3.5)

project(nokia-test-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories("include")

set(HEADERS include/table.h include/cell.h include/utils.h include/csvio.h include/errors.h)
set(SOURCES sources/main.cpp sources/table.cpp sources/cell.cpp sources/csvio.cpp sources/utils.cpp)

add_executable(nokia-test-task ${SOURCES} ${HEADERS})
