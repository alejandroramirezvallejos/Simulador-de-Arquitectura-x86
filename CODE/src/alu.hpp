#pragma once
#include "../include/tipos.hpp"

class EstadoCPU;

class ALU {
public:
    static Palabra sumar(Palabra a, Palabra b, EstadoCPU& cpu);
    static Palabra restar(Palabra a, Palabra b, EstadoCPU& cpu);
    static void comparar(Palabra a, Palabra b, EstadoCPU& cpu);
};
