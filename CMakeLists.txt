cmake_minimum_required(VERSION 3.17)
project(LineUp4)

set(CMAKE_CXX_STANDARD 14)

add_executable(LineUp4
        src/main.cpp
        src/Game.cpp include/Game.h
        include/AI.h
        src/MinimaxAI.cpp include/MinimaxAI.h)