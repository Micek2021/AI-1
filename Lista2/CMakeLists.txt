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
        src/algortihms/Agent.h
        src/genetic/genetic_algorithm.cpp
        src/genetic/genetic_algorithm.h
        src/tests/test_genetic.cpp
        src/tests/test_genetic.h
        src/tests/test_tournament.cpp
        src/tests/test_tournament.h
        src/tests/test_benchmark.cpp
        src/tests/test_benchmark.h
        src/tests/test_game.cpp
        src/tests/test_game.h)

include_directories(src/algortihms src/board src/tests src/genetic)