#include "memoria.hpp"
#include <algorithm>

Memoria::Memoria() {
    std::ranges::fill(memoria, 0);
}

Numero Memoria::leer_numero(const Direccion direccion) const {
    if (direccion + 7 >= 1024) return 0;

    Numero resultado = 0;

    for (int i = 0; i < 8; ++i)
        resultado |= static_cast<Numero>(memoria[direccion + i]) << (i * 8);

    return resultado;
}

void Memoria::escribir_numero(const Direccion direccion, const Numero numero) {
    if (direccion + 7 >= 1024) return;

    for (int i = 0; i < 8; ++i)
        memoria[direccion + i] = static_cast<Byte>((numero >> (i * 8)) & 0xFF);
}

Byte Memoria::leer_byte(const Direccion direccion) const {
    return (direccion >= 1024) ? 0 : memoria[direccion];
}

void Memoria::escribir_byte(const Direccion direccion, const Byte valor) {
    if (direccion < 1024) memoria[direccion] = valor;
}

Numero Memoria::leer(const Direccion direccion) const {
    return leer_numero(direccion);
}

void Memoria::escribir(const Direccion direccion, const Numero valor) {
    escribir_numero(direccion, valor);
}
