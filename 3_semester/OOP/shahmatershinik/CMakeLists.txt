cmake_minimum_required(VERSION 3.20)
project(Chess)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

set(SOURCES
    "src/board.cpp"
    "src/chessGame.cpp"
    "src/main.cpp"
    "src/piece.cpp"
    "src/pieceTextures.cpp"
    "src/network.cpp"
    

    "include/board.h"
    "include/chessGame.h"
    "include/piece.h"
    "include/pieceTextures.h"
    "include/network.h"
    
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_include_directories(${PROJECT_NAME} PUBLIC include)
