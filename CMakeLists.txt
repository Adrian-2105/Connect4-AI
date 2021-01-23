cmake_minimum_required(VERSION 3.17)
project(Connect4-AI)

set(CMAKE_CXX_STANDARD 14)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")

#set(SFML_INCLUDE_DIR "/home/adrian/Libraries/SFML-2.5.1/include")
#set(SFML_LIBRARY_DIR "/home/adrian/Libraries/SFML-2.5.1/lib")
#set(SFML_DIR "/home/adrian/Libraries/SFML-2.5.1/lib/cmake/SFML")

#link_directories(SFML_LIBRARY_DIR)
#include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Connect4-AI
        src/main.cpp
        src/Game.cpp include/Game.h
        include/AI.h
        src/MinimaxAI.cpp include/MinimaxAI.h)

target_link_libraries (Connect4-AI sfml-audio sfml-graphics sfml-window sfml-system)