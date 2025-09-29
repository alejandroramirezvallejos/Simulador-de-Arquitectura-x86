#pragma once
#include "../include/tipos.hpp"

class Memoria {
    public:
        Byte memoria[1024]{};

        Memoria();

        [[nodiscard]] Numero leer_numero(Direccion direccion) const;
        void escribir_numero(Direccion direccion, Numero numero);
        [[nodiscard]] Byte leer_byte(Direccion direccion) const;
        void escribir_byte(Direccion direccion, Byte valor);
};
