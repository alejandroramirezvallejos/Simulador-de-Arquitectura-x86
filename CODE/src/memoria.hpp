#pragma once
#include "../include/tipos.hpp"

class Memoria {
public:
    Palabra leer_palabra(Direccion direccion) const;
    void escribir_palabra(Direccion direccion, Palabra valor);

    Byte leer_byte(Direccion direccion) const;
    void escribir_byte(Direccion direccion, Byte valor);
};
