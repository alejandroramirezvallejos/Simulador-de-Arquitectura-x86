#pragma once
#include <cstdint>
#include <string>

using Numero = std::uint64_t;
using Direccion = std::uint64_t;
using Byte = std::uint8_t;

enum class Registro : int {
    RAX = 0,
    RBX = 1,
    RCX = 2,
    RDX = 3,
    RSP = 4,
    RBP = 5,
    RSI = 6,
    RDI = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,
    RIP = 16
};

enum class RegistroInterno : int {
    RIM = 0,
    RMD = 1,
    RI = 2,
    REN1 = 3,
    REN2 = 4,
    ACUMULADOR = 5,
    RESTADOR = 6,
    SECUENCIADOR = 7
};

enum class Bandera : int {
    CERO = 0,
    ACARREO = 1,
    SIGNO = 2,
};

enum class Comando : int {
    MOVQ = 0,
    MOVL = 1,
    ADDQ = 2,
    ADDL = 3,
    SUBQ = 4,
    SUBL = 5,
    PUSHQ = 6,
    POPQ = 7,
    JMP = 8,
    LOAD = 9,
    STORE = 10,
    NOP = 11
};

struct AccionDebug {
    std::string tipo_instruccion;
    std::string descripcion;
    std::string registro_afectado;
    Numero valor_anterior;
    Numero valor_nuevo;
    Direccion direccion_memoria;
    std::string fuente_datos;
    std::string estado_registros_internos;

    AccionDebug() : valor_anterior(0), valor_nuevo(0), direccion_memoria(0) {}
};

enum class SelectorMemoria : int {
    RAM = 0,
    CACHE_L1 = 1,
    CACHE_L2 = 2,
    CACHE_L3 = 3
};
