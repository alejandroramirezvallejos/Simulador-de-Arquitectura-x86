#pragma once
#include "../include/tipos.hpp"

class CPU;

class ALU {
    public:
        static Numero sumar(Numero a, Numero b, CPU& cpu);
        static Numero restar(Numero a, Numero b, CPU& cpu);
        static void comparar(Numero a, Numero b, CPU& cpu);
};
