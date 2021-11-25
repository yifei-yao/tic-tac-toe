cmake_minimum_required(VERSION 3.20)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 17)

add_executable(tic_tac_toe src/main.cpp src/board.cpp src/board.h src/game.cpp src/game.h src/role.cpp src/role.h src/move.h src/minimax.cpp src/minimax.h)
