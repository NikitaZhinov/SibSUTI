cmake_minimum_required(VERSION 3.20)
project(GameOfLife LANGUAGES CXX)
# standart
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#doxygen
if (DOCS)
  add_subdirectory(docs)
endif()

#sfml
find_package(sfml-graphics)
find_package(sfml-window)
find_package(sfml-system)


#Target Configurations
file(GLOB SOURCE_FILE src/*.cpp)
add_executable(GameOfLifeMain ${SOURCE_FILE}) # Change target name here

# sfml
target_link_libraries(GameOfLifeMain PRIVATE sfml-graphics)
target_link_libraries(GameOfLifeMain PRIVATE sfml-window)
target_link_libraries(GameOfLifeMain PRIVATE sfml-system)

# Add gtest
add_executable(GameOfLifeTests test/test.cpp src/gameoflife.cpp) # Change target name here
target_link_libraries(GameOfLifeTests PRIVATE gtest sfml-graphics sfml-window sfml-system)
add_test(NAME GameOfLifeTests COMMAND GameOfLifeTests)

enable_testing()
