cmake_minimum_required(VERSION 4.0)
project(EXAMEN)

set(CMAKE_CXX_STANDARD 20)

add_executable(EXAMEN main.cpp
        src/parser.cpp
        src/estado_cpu.cpp
        include/salida_json.hpp
        src/alu.cpp
        src/memoria.cpp
        src/motor_simulacion.cpp)
