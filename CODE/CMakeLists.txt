cmake_minimum_required(VERSION 3.10)
project(CODE)

set(CMAKE_CXX_STANDARD 20)

add_executable(CODE main.cpp
        src/parser.cpp
        src/estado_cpu.cpp
        src/alu.cpp
        src/memoria.cpp
        src/motor_simulacion.cpp)
