#include <iostream>
#include <fstream>
#include <cstring>
#include "src/motor_simulacion.hpp"
using namespace std;

string obtener_nombre_comando(const Comando tipo) {
    switch (tipo) {
        case Comando::MOVQ: return "MOVQ";
        case Comando::MOVL: return "MOVL";
        case Comando::ADDQ: return "ADDQ";
        case Comando::ADDL: return "ADDL";
        case Comando::SUBQ: return "SUBQ";
        case Comando::SUBL: return "SUBL";
        case Comando::PUSHQ: return "PUSHQ";
        case Comando::POPQ: return "POPQ";
        case Comando::JMP: return "JMP";
        case Comando::LOAD: return "LOAD";
        case Comando::STORE: return "STORE";
        case Comando::NOP: return "NOP";
        default: return "DESCONOCIDO";
    }
}

string obtener_nombre_registro(const Registro reg) {
    switch (reg) {
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
        default: return "DESCONOCIDO";
    }
}

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define EXPORT __attribute__((visibility("default")))
#else
    #define EXPORT
#endif

extern "C" {
    static MotorSimulacion* simulador = nullptr;

    EXPORT int inicializar() {
        simulador = new MotorSimulacion();
        return 1;
    }

    EXPORT int cargar(const char* archivo) {
        if (!simulador) return 0;
        simulador->cargar_programa(string(archivo));
        return 1;
    }

    EXPORT int ejecutar_paso() {
        if (!simulador) return 0;
        simulador->siguiente_paso();
        return static_cast<int>(simulador->esta_ejecutando());
    }

    EXPORT int reiniciar() {
        if (!simulador) return 0;
        simulador->reiniciar();
        return 1;
    }

    EXPORT int limpiar() {
        if (simulador) {
            delete simulador;
            simulador = nullptr;
        }
        return 1;
    }

    EXPORT void obtener_estado(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        const string estado = simulador->obtener_estado();
        strncpy(buffer, estado.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_estado_cache(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        const string estado = simulador->obtener_estado_con_caches();
        strncpy(buffer, estado.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_memoria(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        const string memoria = simulador->obtener_memoria();
        strncpy(buffer, memoria.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_instruccion_actual(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        const string debug = simulador->obtener_debug_info();
        strncpy(buffer, debug.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_historial(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        const string historial = simulador->obtener_historial_debug();
        strncpy(buffer, historial.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_registros_internos(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        const string internos = simulador->obtener_registros_internos();
        strncpy(buffer, internos.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT int limpiar_historial() {
        if (!simulador) return 0;
        simulador->limpiar_debug();
        return 1;
    }

    EXPORT int esta_ejecutando() {
        if (!simulador) return 0;
        return static_cast<int>(simulador->esta_ejecutando());
    }
}

int main() {
    cout << "=== PRUEBA COMPLETA DE API DLL SIMULADOR x86 ===\n\n";

    char buffer[2048];

    cout << "1. PRUEBAS DE INICIALIZACION\n";
    int resultado = inicializar();
    cout << "   - Resultado inicializar(): Exito\n\n";

    cout << "2. DEBUG DETALLADO DEL PARSER\n";
    cout << "   - Intentando cargar ../entrada.asm...\n";

    if (ifstream archivo_test("../entrada.asm"); archivo_test.is_open()) {
        cout << "   - Archivo encontrado, analizando linea por linea...\n";
        string linea;
        int num_linea = 1;

        while (getline(archivo_test, linea)) {
            cout << "     Linea " << num_linea << ": '" << linea << "'\n";

            auto instruccion = Parser::analizar_linea(linea);
            cout << "       -> Tipo: " << static_cast<int>(instruccion.tipo) << " (" << obtener_nombre_comando(instruccion.tipo) << ")\n";
            cout << "       -> Reg destino: " << obtener_nombre_registro(instruccion.registro_destino) << "\n";
            cout << "       -> Reg origen: " << obtener_nombre_registro(instruccion.registro_origen) << "\n";
            cout << "       -> Usa inmediato: " << (instruccion.usar_numero_inmediato ? "SI" : "NO");
            if (instruccion.usar_numero_inmediato) cout << " (valor: " << instruccion.numero_inmediato << ")";
            cout << "\n";
            cout << "       -> Usa memoria: " << (instruccion.usar_direccion_memoria ? "SI" : "NO");
            if (instruccion.usar_direccion_memoria) cout << " (direccion: " << instruccion.direccion_memoria << ")";
            cout << "\n\n";

            num_linea++;
        }
        archivo_test.close();
    } else {
        cout << "   - ERROR: No se pudo abrir el archivo\n";
    }

    cout << "3. CARGA COMPLETA DEL PROGRAMA\n";
    const auto programa_completo = Parser::cargar_programa("../entrada.asm");
    cout << "   - Instrucciones cargadas: " << programa_completo.size() << "\n";

    for (size_t i = 0; i < programa_completo.size() && i < 5; i++) {
        const auto& inst = programa_completo[i];
        cout << "     [" << i << "] " << obtener_nombre_comando(inst.tipo) << " ";
        if (inst.usar_numero_inmediato) cout << "$" << inst.numero_inmediato << " ";
        if (inst.usar_direccion_memoria) cout << "[" << inst.direccion_memoria << "] ";
        cout << obtener_nombre_registro(inst.registro_destino) << "\n";
    }

    cout << "\n4. PRUEBAS COMPLETAS DE LA API DLL\n";

    cout << "   4.1 Cargando programa...\n";
    resultado = cargar("../entrada.asm");
    cout << "       cargar(): " << (resultado ? "OK" : "ERROR") << "\n";

    cout << "   4.2 Verificando estado...\n";
    cout << "       esta_ejecutando(): " << (esta_ejecutando() ? "SI" : "NO") << "\n";

    cout << "   4.3 Estado inicial...\n";
    obtener_estado(buffer, sizeof(buffer));
    cout << "       obtener_estado():\n" << buffer << "\n";

    cout << "   4.4 Estado con cache...\n";
    obtener_estado_cache(buffer, sizeof(buffer));
    cout << "       obtener_estado_cache():\n" << buffer << "\n";

    cout << "   4.5 Registros internos...\n";
    obtener_registros_internos(buffer, sizeof(buffer));
    cout << "       obtener_registros_internos(): " << buffer << "\n\n";

    cout << "   4.6 Memoria inicial...\n";
    obtener_memoria(buffer, sizeof(buffer));
    cout << "       obtener_memoria() (primeros 100 chars): " << string(buffer).substr(0, 100) << "...\n\n";

    cout << "5. EJECUCION PASO A PASO\n";
    int paso = 1;
    while (esta_ejecutando() && paso <= 8) {
        cout << "   PASO " << paso << ":\n";

        obtener_instruccion_actual(buffer, sizeof(buffer));
        cout << "     obtener_instruccion_actual(): " << buffer << "\n";

        resultado = ejecutar_paso();
        cout << "     ejecutar_paso(): " << (resultado ? "Continua" : "Terminado") << "\n";

        obtener_estado(buffer, sizeof(buffer));
        cout << "     Estado: " << buffer << "\n";

        obtener_historial(buffer, sizeof(buffer));
        cout << "     Historial: " << buffer << "\n\n";

        paso++;
    }

    cout << "6. PRUEBAS DE LIMPIEZA Y RESET\n";

    cout << "   6.1 Limpiar historial...\n";
    resultado = limpiar_historial();
    cout << "       limpiar_historial(): " << (resultado ? "OK" : "ERROR") << "\n";

    obtener_historial(buffer, sizeof(buffer));
    cout << "       Historial despues de limpiar: " << buffer << "\n\n";

    cout << "   6.2 Reiniciar simulador...\n";
    resultado = reiniciar();
    cout << "       reiniciar(): " << (resultado ? "OK" : "ERROR") << "\n";
    cout << "       esta_ejecutando(): " << (esta_ejecutando() ? "SI" : "NO") << "\n\n";

    cout << "   6.3 Segunda carga y ejecucion rapida...\n";
    cargar("../entrada.asm");
    for (int i = 1; i <= 3 && esta_ejecutando(); i++) {
        obtener_instruccion_actual(buffer, sizeof(buffer));
        cout << "       Paso " << i << ": " << buffer;
        ejecutar_paso();
        cout << " -> Ejecutado\n";
    }

    cout << "\n7. CLEANUP FINAL\n";
    resultado = limpiar();
    cout << "   limpiar(): OK\n";

    cout << "\n=== RESUMEN API DLL ===\n";
    cout << "inicializar() - Crear simulador\n";
    cout << "cargar() - Cargar archivo ASM\n";
    cout << "ejecutar_paso() - Ejecutar siguiente instruccion\n";
    cout << "esta_ejecutando() - Verificar si hay programa activo\n";
    cout << "obtener_estado() - Estado basico CPU\n";
    cout << "obtener_estado_cache() - Estado + cache L1/L2/L3\n";
    cout << "obtener_memoria() - Volcado JSON de memoria\n";
    cout << "obtener_instruccion_actual() - Debug instruccion actual\n";
    cout << "obtener_historial() - Historial completo JSON\n";
    cout << "obtener_registros_internos() - Registros internos CPU\n";
    cout << "limpiar_historial() - Borrar historial debug\n";
    cout << "reiniciar() - Reset simulador\n";
    cout << "limpiar() - Liberar memoria\n";
    cout << "\nTODAS LAS FUNCIONES PROBADAS!\n";

    return 0;
}
