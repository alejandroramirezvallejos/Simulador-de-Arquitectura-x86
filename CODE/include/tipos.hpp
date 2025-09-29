#pragma once
#include <cstdint>

using Numero = std::uint32_t;
using Direccion = std::uint32_t;
using Byte = std::uint8_t;

enum class Registro : int {
    EAX = 0,
    EBX = 1,
    ECX = 2,
    EDX = 3,
    ESP = 4,
    EBP = 5,
    ESI = 6,
    EDI = 7
};

enum class Bandera : int {
    CERO = 0,
    ACARREO = 1,
    SIGNO = 2
};

enum class Comando : int {
    MOV = 0,
    ADD = 1,
    SUB = 2,
    JMP = 3,
    LOAD = 4,
    STORE = 5,
    NOP = 6
};
