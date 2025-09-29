#include "alu.hpp"
#include "cpu.hpp"

Numero ALU::sumar(Numero a, Numero b, CPU& cpu) {
    const Numero resultado = a + b;

    cpu.establecer_bandera(Bandera::CERO, resultado == 0);
    cpu.establecer_bandera(Bandera::ACARREO, resultado < a);
    cpu.establecer_bandera(Bandera::SIGNO, resultado > 2147483647);

    return resultado;
}

Numero ALU::restar(Numero a, Numero b, CPU& cpu) {
    const Numero resultado = a - b;

    cpu.establecer_bandera(Bandera::CERO, resultado == 0);
    cpu.establecer_bandera(Bandera::ACARREO, a < b);
    cpu.establecer_bandera(Bandera::SIGNO, resultado > 2147483647);

    return resultado;
}

void ALU::comparar(Numero a, Numero b, CPU& cpu) {
    cpu.establecer_bandera(Bandera::CERO, a == b);
    cpu.establecer_bandera(Bandera::ACARREO, a < b);
    cpu.establecer_bandera(Bandera::SIGNO, false);
}