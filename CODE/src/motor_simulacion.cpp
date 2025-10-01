#include "motor_simulacion.hpp"
#include <sstream>
#include <iomanip>

void MotorSimulacion::cargar_programa(const string& nombre_archivo) {
    programa = Parser::cargar_programa(nombre_archivo);
    if (!programa.empty()) {
        reiniciar();
        ejecutando = true;
    }
    else ejecutando = false;
}

void MotorSimulacion::siguiente_paso() {
    if (cpu.obtener_contador() >= programa.size()) {
        ejecutando = false;
        return;
    }

    const auto& instruccion = programa[cpu.obtener_contador()];
    ejecutarInstruccion(instruccion);

    if (instruccion.tipo != Comando::JMP)
        cpu.establecer_contador(cpu.obtener_contador() + 1);
}

void MotorSimulacion::ejecutarInstruccion(const InstruccionPrograma& instruccion) {
    switch (instruccion.tipo) {
        case Comando::MOVQ:
            ejecutarMovq(instruccion);
            break;
        case Comando::MOVL:
            ejecutarMovl(instruccion);
            break;
        case Comando::ADDQ:
            ejecutarAddq(instruccion);
            break;
        case Comando::ADDL:
            ejecutarAddl(instruccion);
            break;
        case Comando::SUBQ:
            ejecutarSubq(instruccion);
            break;
        case Comando::SUBL:
            ejecutarSubl(instruccion);
            break;
        case Comando::PUSHQ:
            ejecutarPushq(instruccion);
            break;
        case Comando::POPQ:
            ejecutarPopq(instruccion);
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
        default: ;
    }
}

void MotorSimulacion::ejecutarMovq(const InstruccionPrograma& instruccion) {
    const Numero anterior = cpu.obtener_registro(instruccion.registro_destino);
    const Numero nuevo = instruccion.usar_numero_inmediato ?
                  instruccion.numero_inmediato :
                  cpu.obtener_registro(instruccion.registro_origen);

    cpu.establecer_registro(instruccion.registro_destino, nuevo);
    debugger.mov(obtener_registro(instruccion.registro_destino), anterior, nuevo);
}

void MotorSimulacion::ejecutarMovl(const InstruccionPrograma& instruccion) {
    if (instruccion.usar_direccion_memoria) {
        const Numero direccion_base = cpu.obtener_registro(instruccion.registro_origen);
        const Numero direccion_final = direccion_base + instruccion.direccion_memoria;

        if (instruccion.usar_numero_inmediato) {
            memoria.escribir_numero(direccion_final, instruccion.numero_inmediato & 0xFFFFFFFF);
            debugger.memoria("MOVL", direccion_final, instruccion.numero_inmediato);
        }
        else {
            const Numero valor = memoria.leer_numero(direccion_final) & 0xFFFFFFFF;
            cpu.establecer_registro(instruccion.registro_destino, valor);
            debugger.memoria("MOVL", direccion_final, valor);
        }
    }
    else {
        const Numero anterior = cpu.obtener_registro(instruccion.registro_destino);
        Numero nuevo = instruccion.usar_numero_inmediato ?
                      instruccion.numero_inmediato :
                      cpu.obtener_registro(instruccion.registro_origen);

        nuevo &= 0xFFFFFFFF;
        cpu.establecer_registro(instruccion.registro_destino, nuevo);
        debugger.mov(obtener_registro(instruccion.registro_destino), anterior, nuevo);
    }
}

void MotorSimulacion::ejecutarAddq(const InstruccionPrograma& instruccion) {
    const Numero operando1 = cpu.obtener_registro(instruccion.registro_destino);
    const Numero operando2 = instruccion.usar_numero_inmediato ?
                      instruccion.numero_inmediato :
                      cpu.obtener_registro(instruccion.registro_origen);

    const Numero resultado = operando1 + operando2;

    cpu.establecer_registro(instruccion.registro_destino, resultado);
    actualizar_banderas(resultado, operando1, operando2);
    debugger.operacion("ADDQ", obtener_registro(instruccion.registro_destino), resultado);
}

void MotorSimulacion::ejecutarAddl(const InstruccionPrograma& instruccion) {
    if (instruccion.usar_direccion_memoria) {
        const Numero direccion_base = cpu.obtener_registro(instruccion.registro_origen);
        const Numero direccion_final = direccion_base + instruccion.direccion_memoria;
        const Numero valor_memoria = memoria.leer_numero(direccion_final) & 0xFFFFFFFF;
        const Numero operando2 = instruccion.usar_numero_inmediato ?
                          (instruccion.numero_inmediato & 0xFFFFFFFF) :
                          (cpu.obtener_registro(instruccion.registro_origen) & 0xFFFFFFFF);

        const Numero resultado = (valor_memoria + operando2) & 0xFFFFFFFF;
        cpu.establecer_registro(instruccion.registro_destino, resultado);
        actualizar_banderas(resultado, valor_memoria, operando2);
        debugger.operacion("ADDL", obtener_registro(instruccion.registro_destino), resultado);
    }
    else {
        const Numero operando1 = cpu.obtener_registro(instruccion.registro_destino) & 0xFFFFFFFF;
        const Numero operando2 = instruccion.usar_numero_inmediato ?
                          (instruccion.numero_inmediato & 0xFFFFFFFF) :
                          (cpu.obtener_registro(instruccion.registro_origen) & 0xFFFFFFFF);

        const Numero resultado = (operando1 + operando2) & 0xFFFFFFFF;
        cpu.establecer_registro(instruccion.registro_destino, resultado);

        actualizar_banderas(resultado, operando1, operando2);
        debugger.operacion("ADDL", obtener_registro(instruccion.registro_destino), resultado);
    }
}

void MotorSimulacion::ejecutarSubq(const InstruccionPrograma& instruccion) {
    const Numero operando1 = cpu.obtener_registro(instruccion.registro_destino);
    const Numero operando2 = instruccion.usar_numero_inmediato ?
                      instruccion.numero_inmediato :
                      cpu.obtener_registro(instruccion.registro_origen);

    const Numero resultado = operando1 - operando2;
    cpu.establecer_registro(instruccion.registro_destino, resultado);

    actualizar_banderas(resultado, operando1, operando2);
    debugger.operacion("SUBQ", obtener_registro(instruccion.registro_destino), resultado);
}

void MotorSimulacion::ejecutarSubl(const InstruccionPrograma& instruccion) {
    const Numero operando1 = cpu.obtener_registro(instruccion.registro_destino) & 0xFFFFFFFF;
    const Numero operando2 = instruccion.usar_numero_inmediato ?
                      (instruccion.numero_inmediato & 0xFFFFFFFF) :
                      (cpu.obtener_registro(instruccion.registro_origen) & 0xFFFFFFFF);

    const Numero resultado = (operando1 - operando2) & 0xFFFFFFFF;
    cpu.establecer_registro(instruccion.registro_destino, resultado);

    actualizar_banderas(resultado, operando1, operando2);
    debugger.operacion("SUBL", obtener_registro(instruccion.registro_destino), resultado);
}

void MotorSimulacion::ejecutarPushq(const InstruccionPrograma& instruccion) {
    const Numero numero = instruccion.usar_numero_inmediato ?
                  instruccion.numero_inmediato :
                  cpu.obtener_registro(instruccion.registro_origen);

    cpu.push(numero);
    debugger.pila("PUSHQ", numero);
}

void MotorSimulacion::ejecutarPopq(const InstruccionPrograma& instruccion) {
    const Numero numero = cpu.pop();
    cpu.establecer_registro(instruccion.registro_destino, numero);
    debugger.pila("POPQ", numero);
}

void MotorSimulacion::ejecutarJmp(const InstruccionPrograma& instruccion) {
    const Numero anterior = cpu.obtener_contador();
    const Numero nueva = instruccion.numero_inmediato;

    cpu.establecer_contador(nueva);
    debugger.salto(anterior, nueva);
}

void MotorSimulacion::ejecutarLoad(const InstruccionPrograma& instruccion) {
    const Numero numero = memoria.leer(instruccion.direccion_memoria);
    cpu.establecer_registro(instruccion.registro_destino, numero);
    debugger.memoria("LOAD", instruccion.direccion_memoria, numero);
}

void MotorSimulacion::ejecutarStore(const InstruccionPrograma& instruccion) {
    const Numero numero = cpu.obtener_registro(instruccion.registro_origen);
    memoria.escribir(instruccion.direccion_memoria, numero);
    debugger.memoria("STORE", instruccion.direccion_memoria, numero);
}

void MotorSimulacion::actualizar_banderas(const Numero resultado, const Numero operando1, Numero operando2) {
    const bool cero_anterior = cpu.obtener_bandera(Bandera::CERO);
    const bool acarreo_anterior = cpu.obtener_bandera(Bandera::ACARREO);
    const bool signo_anterior = cpu.obtener_bandera(Bandera::SIGNO);

    const bool cero_nuevo = (resultado == 0);
    const bool signo_nuevo = (resultado & 0x8000000000000000ULL) != 0;
    const bool acarreo_nuevo = (resultado < operando1);

    cpu.establecer_bandera(Bandera::CERO, cero_nuevo);
    cpu.establecer_bandera(Bandera::SIGNO, signo_nuevo);
    cpu.establecer_bandera(Bandera::ACARREO, acarreo_nuevo);

    if (cero_anterior != cero_nuevo)
        debugger.bandera("CERO", cero_anterior, cero_nuevo);

    if (acarreo_anterior != acarreo_nuevo)
        debugger.bandera("ACARREO", acarreo_anterior, acarreo_nuevo);

    if (signo_anterior != signo_nuevo)
        debugger.bandera("SIGNO", signo_anterior, signo_nuevo);
}

string MotorSimulacion::obtener_registro(const Registro registro) {
    switch (registro) {
        case Registro::RAX: return "RAX";
        case Registro::RBX: return "RBX";
        case Registro::RCX: return "RCX";
        case Registro::RDX: return "RDX";
        case Registro::RSP: return "RSP";
        case Registro::RBP: return "RBP";
        case Registro::RSI: return "RSI";
        case Registro::RDI: return "RDI";
        case Registro::R8: return "R8";
        case Registro::R9: return "R9";
        case Registro::R10: return "R10";
        case Registro::R11: return "R11";
        case Registro::R12: return "R12";
        case Registro::R13: return "R13";
        case Registro::R14: return "R14";
        case Registro::R15: return "R15";
        case Registro::RIP: return "RIP";
        default: return "UNKNOWN";
    }
}

string MotorSimulacion::obtener_debug_info() const {
    return debugger.ultima_accion();
}

string MotorSimulacion::obtener_registros_internos() const {
    return Debugger::estado_registros(cpu);
}

string MotorSimulacion::obtener_historial_debug() const {
    return debugger.historial();
}

string MotorSimulacion::obtener_selector_memoria() const {
    return R"({"fuente":")" + ultima_fuente + "\"}";
}

string MotorSimulacion::obtener_memoria() const {
    std::ostringstream json;
    json << "{\n";
    json << "  \"memoria_ram\": {\n";
    json << "    \"tamaño_total\": 1024,\n";
    json << "    \"datos\": [\n";

    for (int i = 0; i < 1024; i += 8) {
        if (i > 0) json << ",\n";

        const Numero valor = memoria.leer_numero(i);

        json << "      {\n";
        json << R"(        "direccion": "0x)" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << i << "\",\n";
        json << "        \"direccion_decimal\": " << std::dec << i << ",\n";
        json << "        \"valor\": " << valor << ",\n";
        json << R"(        "valor_hex": "0x)" << std::hex << std::uppercase << valor << "\"\n";
        json << "      }";
    }

    json << "\n    ]\n";
    json << "  }\n";
    json << "}";

    return json.str();
}

void MotorSimulacion::limpiar_debug() {
    debugger.limpiar();
}

void MotorSimulacion::reiniciar() {
    cpu = CPU{};
    memoria = Memoria{};
    caches = JerarquiaCache{};
    debugger.limpiar();
    ejecutando = true;
    ultima_fuente = "RAM";
}

string MotorSimulacion::obtener_estado() const {
    std::ostringstream estado;

    estado << "Contador: " << cpu.obtener_contador() << "\n";
    estado << "RAX: " << cpu.obtener_registro(Registro::RAX) << "\n";
    estado << "RBX: " << cpu.obtener_registro(Registro::RBX) << "\n";
    estado << "RCX: " << cpu.obtener_registro(Registro::RCX) << "\n";
    estado << "RDX: " << cpu.obtener_registro(Registro::RDX) << "\n";
    estado << "RSP: " << cpu.obtener_registro(Registro::RSP) << "\n";
    estado << "RBP: " << cpu.obtener_registro(Registro::RBP) << "\n";
    estado << "RSI: " << cpu.obtener_registro(Registro::RSI) << "\n";
    estado << "RDI: " << cpu.obtener_registro(Registro::RDI) << "\n";
    estado << "Banderas - CERO: " << (cpu.obtener_bandera(Bandera::CERO) ? "1" : "0")
           << " ACARREO: " << (cpu.obtener_bandera(Bandera::ACARREO) ? "1" : "0")
           << " SIGNO: " << (cpu.obtener_bandera(Bandera::SIGNO) ? "1" : "0") << "\n";

    return estado.str();
}

string MotorSimulacion::obtener_estado_con_caches() const {
    return obtener_estado() + caches.obtener_estadisticas();
}

bool MotorSimulacion::esta_ejecutando() const {
    return ejecutando;
}
