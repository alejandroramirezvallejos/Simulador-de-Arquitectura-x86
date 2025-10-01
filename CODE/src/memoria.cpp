#include "memoria.hpp"
#include <algorithm>
#include <cstring>

Memoria::Memoria() {
    std::memset(memoria, 0, sizeof(memoria));
}

Numero Memoria::leer_numero(const Direccion direccion) const {
    if (direccion + 3 >= 1024) return 0;

    return memoria[direccion] + (memoria[direccion + 1] * 256)
           + (memoria[direccion + 2] * 65536) + (memoria[direccion + 3]
           * 16777216);
}

void Memoria::escribir_numero(const Direccion direccion, const Numero numero) {
    if (direccion + 3 >= 1024) return;

    memoria[direccion] = numero % 256;
    memoria[direccion + 1] = (numero / 256) % 256;
    memoria[direccion + 2] = (numero / 65536) % 256;
    memoria[direccion + 3] = (numero / 16777216) % 256;
}

Byte Memoria::leer_byte(const Direccion direccion) const {
    if (direccion >= 1024) return 0;
    return memoria[direccion];
}

void Memoria::escribir_byte(const Direccion direccion, const Byte valor) {
    if (direccion >= 1024) return;
    memoria[direccion] = valor;
}
