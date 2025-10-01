#include <iostream>
#include <fstream>
#include <cstring>
#include "src/motor_simulacion.hpp"
#include "include/salida_json.hpp"
using namespace std;

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define EXPORT __attribute__((visibility("default")))
#else
    #define EXPORT
#endif

extern "C" {
    static MotorSimulacion* simulador = nullptr;

    EXPORT int inicializar_simulador() {
        simulador = new MotorSimulacion();
        return 1;
    }

    EXPORT int cargar_programa(const char* archivo) {
        if (!simulador) return 0;
        simulador->cargar_programa(string(archivo));
        return 1;
    }

    EXPORT int ejecutar_paso() {
        if (!simulador) return 0;
        simulador->siguiente_paso();
        return static_cast<int>(simulador->esta_ejecutando());
    }

    EXPORT void obtener_estado_buffer(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;
        
        const string estado = simulador->obtener_estado();
        
        strncpy(buffer, estado.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_estado_con_caches_buffer(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;

        const string estado = simulador->obtener_estado_con_caches();

        strncpy(buffer, estado.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_registros_buffer(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;

        const string registros = SalidaJson::serializar_registros(simulador->cpu);

        strncpy(buffer, registros.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_memoria_buffer(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;

        const string memoria = SalidaJson::serializar_memoria(simulador->memoria);

        strncpy(buffer, memoria.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void obtener_caches_buffer(char* buffer, const int tamaño) {
        if (!simulador || !buffer || tamaño <= 0) return;

        const string caches = SalidaJson::serializar_caches(simulador->caches);

        strncpy(buffer, caches.c_str(), tamaño - 1);
        buffer[tamaño - 1] = '\0';
    }

    EXPORT void reiniciar() {
        if (simulador) simulador->reiniciar();
    }

    EXPORT void finalizar_simulador() {
        if (simulador) {
            delete simulador;
            simulador = nullptr;
        }
    }
}

int main() {
    //TODO: Es solo un archivo de ejemplo en la practica se usara Excel con VB

    cout << "Simulador de Arquitectura x86 con Caches\n=========================================\n\n";
    const string archivo_asm = "programa_ejemplo.asm";
    ofstream ejemplo(archivo_asm);

    if (!ejemplo.is_open()) {
        cout << "ERROR: No se pudo crear " << archivo_asm << endl;
        return 1;
    }

    ejemplo << "MOV EAX, 100\n";
    ejemplo << "STORE EAX, 0\n";
    ejemplo << "MOV EBX, 200\n";
    ejemplo << "STORE EBX, 4\n";
    ejemplo << "LOAD ECX, 0\n";
    ejemplo << "LOAD EDX, 4\n";
    ejemplo << "ADD ECX, EDX\n";
    ejemplo << "STORE ECX, 8\n";
    ejemplo.close();

    cout << "Archivo " << archivo_asm << " creado exitosamente.\n\n";

    MotorSimulacion motor;
    motor.cargar_programa(archivo_asm);

    if (!motor.esta_ejecutando()) {
        cout << "ERROR: El programa no se cargo correctamente.\n";
        return 1;
    }

    cout << "Programa cargado. Ejecutando paso a paso:\n\n";
    cout << "Estado inicial:\n" << motor.obtener_estado_con_caches() << "\n\n";

    for (int paso = 1; motor.esta_ejecutando(); ++paso) {
        cout << "Ejecutando paso " << paso << '\n';
        motor.siguiente_paso();
        cout << "Despues del paso " << paso << ":\n" << motor.obtener_estado_con_caches() << "\n\n";

        if (paso > 15) {
            cout << "ERROR: Demasiados pasos.\n";
            break;
        }
    }

    cout << "Ejecucion completada.\n";
    return 0;
}