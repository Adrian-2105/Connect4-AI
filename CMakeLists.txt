cmake_minimum_required(VERSION 3.17)
project(Connect4-AI)
set(CMAKE_PROJECT_NAME)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME}
        src/main.cpp
        src/Game.cpp include/Game.h
        include/AI.h
        src/MinimaxAI.cpp include/MinimaxAI.h)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)