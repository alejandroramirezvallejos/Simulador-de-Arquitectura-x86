#include "cpu.hpp"

Numero CPU::obtener_registro(Registro registro) const noexcept {
    return registros[static_cast<int>(registro)];
}

void CPU::establecer_registro(Registro registro, const Numero numero) noexcept {
    registros[static_cast<int>(registro)] = numero;
}

Numero CPU::obtener_contador() const noexcept {
    return contador;
}

void CPU::establecer_contador(const Numero numero) noexcept {
    contador = numero;
}

bool CPU::obtener_bandera(Bandera bandera) const noexcept {
    return banderas[static_cast<int>(bandera)];
}

void CPU::establecer_bandera(Bandera bandera, const bool valor) noexcept {
    banderas[static_cast<int>(bandera)] = valor;
}
