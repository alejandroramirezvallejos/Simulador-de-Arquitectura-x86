cmake_minimum_required(VERSION 3.10)
project(CODE)

set(CMAKE_CXX_STANDARD 20)

set(COMMON_SOURCES
    src/parser.cpp
    src/cpu.cpp
    src/alu.cpp
    src/memoria.cpp
    src/cache.cpp
    src/jerarquia_cache.cpp
    src/motor_simulacion.cpp
    src/salida_json.cpp
    src/debugger.cpp
)

add_executable(CODE main.cpp ${COMMON_SOURCES})
add_library(simulador SHARED main.cpp ${COMMON_SOURCES})

if(WIN32)
    set_target_properties(simulador PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
    )
endif()
