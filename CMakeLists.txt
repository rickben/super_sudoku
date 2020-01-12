cmake_minimum_required(VERSION 3.15)
project(hw3 C)

set(CMAKE_C_STANDARD 99)

add_executable(hw3 main.c Parser.c Game.c Solver.c MainAux.c Parser.h Game.h Solver.h MainAux.h SPBufferset.h)