cmake_minimum_required(VERSION 3.5)

project(nokia-test-task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(HEADERS table.h cell.h utils.h csvio.h errors.h)
set(SOURCES main.cpp table.cpp cell.cpp csvio.cpp utils.cpp)

add_executable(nokia-test-task ${SOURCES} ${HEADERS})
