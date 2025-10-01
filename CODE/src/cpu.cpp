#include "cpu.hpp"
#include <sstream>
#include <algorithm>

CPU::CPU() {
    std::fill_n(registros, 17, 0);
    std::fill_n(registros_internos, 8, 0);
    std::fill_n(banderas, 3, false);

    registros[4] = 1024;
    contador = 0;
    puntero = 1024;
}

Numero CPU::obtener_registro(Registro registro) const noexcept {
    return registros[static_cast<int>(registro)];
}

void CPU::establecer_registro(Registro registro, const Numero numero) noexcept {
    registros[static_cast<int>(registro)] = numero;
}

Numero CPU::obtener_registro_interno(RegistroInterno registro) const noexcept {
    return registros_internos[static_cast<int>(registro)];
}

void CPU::establecer_registro_interno(RegistroInterno registro, const Numero numero) noexcept {
    registros_internos[static_cast<int>(registro)] = numero;
}

Numero CPU::obtener_contador() const noexcept {
    return contador;
}

void CPU::establecer_contador(const Numero numero) noexcept {
    contador = numero;
    registros[16] = numero;
}

bool CPU::obtener_bandera(Bandera bandera) const noexcept {
    return banderas[static_cast<int>(bandera)];
}

void CPU::establecer_bandera(Bandera bandera, const bool valor) noexcept {
    banderas[static_cast<int>(bandera)] = valor;
}

void CPU::push(const Numero numero) {
    if (!pila_llena()) {
        --puntero;
        pila[puntero] = numero;
        registros[4] = puntero;
    }
}

Numero CPU::pop() {
    if (!pila_vacia()) {
        const Numero numero = pila[puntero];
        ++puntero;
        registros[4] = puntero;

        return numero;
    }
    return 0;
}

bool CPU::pila_vacia() const noexcept {
    return puntero >= 1024;
}

bool CPU::pila_llena() const noexcept {
    return puntero <= 0;
}

std::string CPU::obtener_estado_registros_internos() const {
    std::ostringstream estado;

    estado << "RIM=" << registros_internos[0] << ", ";
    estado << "RMD=" << registros_internos[1] << ", ";
    estado << "RI=" << registros_internos[2] << ", ";
    estado << "REN1=" << registros_internos[3] << ", ";
    estado << "REN2=" << registros_internos[4] << ", ";
    estado << "ACUM=" << registros_internos[5] << ", ";
    estado << "REST=" << registros_internos[6] << ", ";
    estado << "SEC=" << registros_internos[7];

    return estado.str();
}
