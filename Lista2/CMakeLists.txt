cmake_minimum_required(VERSION 3.29)
project(Breakthrough)

set(CMAKE_CXX_STANDARD 20)

add_executable(Breakthrough src/main.cpp
        src/algortihms/heuristics.cpp
        src/algortihms/heuristics.h
        src/board/move.cpp
        src/board/move.h
        src/algortihms/evaluator.cpp
        src/algortihms/evaluator.h
        src/board/board.cpp
        src/board/board.h
        src/algortihms/Agent.cpp
        src/algortihms/Agent.h)

include_directories(src/algortihms src/board)