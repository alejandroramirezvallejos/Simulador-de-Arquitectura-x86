cmake_minimum_required(VERSION 3.10)
project(CODE)

set(CMAKE_CXX_STANDARD 20)

add_executable(CODE main.cpp
        src/parser.cpp
        src/cpu.cpp
        src/alu.cpp
        src/memoria.cpp
        src/cache.cpp
        src/jerarquia_cache.cpp
        src/motor_simulacion.cpp
        src/salida_json.cpp
)
