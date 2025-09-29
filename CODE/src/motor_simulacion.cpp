#include "motor_simulacion.hpp"
#include "alu.hpp"
#include "../include/salida_json.hpp"

MotorSimulacion::MotorSimulacion() = default;

void MotorSimulacion::cargar_programa(const string& nombre_archivo) {
    programa = Parser::cargar_programa(nombre_archivo);
    ejecutando = !programa.empty();
    cpu.establecer_contador(0);
}

void MotorSimulacion::siguiente_paso() {
    if (!ejecutando || cpu.obtener_contador() >= programa.size()) {
        ejecutando = false;
        return;
    }

    const Numero contador = cpu.obtener_contador();
    const InstruccionPrograma& instruccion = programa[contador];

    ejecutarInstruccion(instruccion);

    if (instruccion.tipo != Comando::JMP)
        cpu.establecer_contador(contador + 1);

    if (cpu.obtener_contador() >= programa.size())
        ejecutando = false;
}

void MotorSimulacion::ejecutarInstruccion(const InstruccionPrograma& instruccion) {
    switch (instruccion.tipo) {
        case Comando::MOV:
            ejecutarMov(instruccion);
            break;
        case Comando::ADD:
            ejecutarAdd(instruccion);
            break;
        case Comando::SUB:
            ejecutarSub(instruccion);
            break;
        case Comando::JMP:
            ejecutarJmp(instruccion);
            break;
        case Comando::LOAD:
            ejecutarLoad(instruccion);
            break;
        case Comando::STORE:
            ejecutarStore(instruccion);
            break;
        case Comando::NOP:
        default:
            break;
    }
}

void MotorSimulacion::ejecutarMov(const InstruccionPrograma& instruccion) {
    if (instruccion.usar_numero_inmediato)
        cpu.establecer_registro(instruccion.registro_destino, instruccion.numero_inmediato);
    else {
        const Numero numero = cpu.obtener_registro(instruccion.registro_origen);
        cpu.establecer_registro(instruccion.registro_destino, numero);
    }
}

void MotorSimulacion::ejecutarAdd(const InstruccionPrograma& instruccion) {
    const Numero numeroA = cpu.obtener_registro(instruccion.registro_destino);
    const Numero numeroB = instruccion.usar_numero_inmediato
        ? instruccion.numero_inmediato
        : cpu.obtener_registro(instruccion.registro_origen);

    const Numero resultado = ALU::sumar(numeroA, numeroB, cpu);
    cpu.establecer_registro(instruccion.registro_destino, resultado);
}

void MotorSimulacion::ejecutarSub(const InstruccionPrograma& instruccion) {
    const Numero numeroA = cpu.obtener_registro(instruccion.registro_destino);
    const Numero numeroB = instruccion.usar_numero_inmediato
        ? instruccion.numero_inmediato
        : cpu.obtener_registro(instruccion.registro_origen);

    const Numero resultado = ALU::restar(numeroA, numeroB, cpu);
    cpu.establecer_registro(instruccion.registro_destino, resultado);
}

void MotorSimulacion::ejecutarJmp(const InstruccionPrograma& instruccion) {
    if (instruccion.usar_numero_inmediato)
        cpu.establecer_contador(instruccion.numero_inmediato);
}

void MotorSimulacion::ejecutarLoad(const InstruccionPrograma& instruccion) {
    if (instruccion.usar_direccion_memoria) {
        const Numero numero = memoria.leer_numero(instruccion.direccion_memoria);
        cpu.establecer_registro(instruccion.registro_destino, numero);
    }
}

void MotorSimulacion::ejecutarStore(const InstruccionPrograma& instruccion) {
    if (instruccion.usar_direccion_memoria) {
        const Numero numero = cpu.obtener_registro(instruccion.registro_origen);
        memoria.escribir_numero(instruccion.direccion_memoria, numero);
    }
}

string MotorSimulacion::obtener_estado() const {
    return SalidaJson::serializar_estado(cpu, memoria);
}

void MotorSimulacion::reiniciar() {
    cpu = CPU();
    memoria = Memoria();
    ejecutando = !programa.empty();
}

bool MotorSimulacion::esta_ejecutando() const {
    return ejecutando;
}
