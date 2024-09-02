cmake_minimum_required(VERSION 3.8)

project(lab12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lab12 main.cpp)

add_library(sorts STATIC sorts.hpp sorts.cpp)
target_link_libraries(lab12 PUBLIC sorts)
