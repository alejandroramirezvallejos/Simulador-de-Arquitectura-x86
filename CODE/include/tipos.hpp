#pragma once
#include <cstdint>

using Palabra = uint32_t;
using Direccion = uint32_t;
using Byte = uint8_t;

enum class Registro {
    EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI
};

enum class Bandera {
    CERO, ACARREO, SIGNO, DESBORDAMIENTO
};

enum class Instruccion {
    MOV, ADD, SUB, JMP, LOAD, STORE, NOP
};
