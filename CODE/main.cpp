#include <iostream>
#include <fstream>
#include "src/motor_simulacion.hpp"
using namespace std;

extern "C" {
    static MotorSimulacion* sim = nullptr;

    //TODO: Implementar para macOS/Linux "__attribute__((visibility("default")))"

    __declspec(dllexport) int inicializar_simulador() {
        sim = new MotorSimulacion();
        return 1;
    }

    __declspec(dllexport) int cargar_programa(const char* archivo) {
        if (!sim) return 0;
        sim->cargar_programa(string(archivo));
        return 1;
    }

    __declspec(dllexport) int ejecutar_paso() {
        if (!sim) return 0;
        sim->siguiente_paso();
        return static_cast<int>(sim->esta_ejecutando());
    }

    __declspec(dllexport) const char* obtener_estado() {
        if (!sim) return "{}";
        static string estado;
        estado = sim->obtener_estado();
        return estado.c_str();
    }

    __declspec(dllexport) void reiniciar() {
        if (sim) sim->reiniciar();
    }

    __declspec(dllexport) void finalizar_simulador() {
        if (sim) {
            delete sim;
            sim = nullptr;
        }
    }
}

int main() {
    //TODO: Es solo un archivo de ejemplo en la practica se usara Excel con VB

    cout << "Simulador de Arquitectura x86\n==============================\n\n";
    string archivo_asm = "programa_ejemplo.asm";
    ofstream ejemplo(archivo_asm);

    if (!ejemplo.is_open()) {
        cout << "ERROR: No se pudo crear " << archivo_asm << endl;
        return 1;
    }

    ejemplo << "MOV EAX, 10\n";
    ejemplo << "MOV EBX, 20\n";
    ejemplo << "ADD EAX, EBX\n";
    ejemplo << "SUB EAX, 5\n";
    ejemplo.close();

    cout << "Archivo " << archivo_asm << " creado exitosamente.\n\n";

    MotorSimulacion motor;
    motor.cargar_programa(archivo_asm);

    if (!motor.esta_ejecutando()) {
        cout << "ERROR: El programa no se cargó correctamente.\n";
        return 1;
    }

    cout << "Programa cargado. Ejecutando paso a paso:\n\n";

    cout << "Estado inicial:\n" << motor.obtener_estado() << "\n\n";

    for (int paso = 1; motor.esta_ejecutando(); ++paso) {
        cout << "Ejecutando paso " << paso << "...\n";
        motor.siguiente_paso();
        cout << "Despues del paso " << paso << ":\n" << motor.obtener_estado() << "\n\n";

        if (paso > 10) {
            cout << "ERROR: Demasiados pasos.\n";
            break;
        }
    }

    cout << "Ejecucion completada.\n";
    return 0;
}