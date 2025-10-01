#include <iostream>
#include "src/motor_simulacion.hpp"
using namespace std;

int main() {
    cout << "=== PRUEBA SIMPLE DEL SIMULADOR x86 ===\n";

    MotorSimulacion simulador;
    cout << "1. Simulador creado\n";

    simulador.cargar_programa("programa_att_ejemplo.asm");
    cout << "2. Programa cargado: " << (simulador.esta_ejecutando() ? "SI" : "NO") << "\n";

    cout << "3. Estado inicial:\n" << simulador.obtener_estado() << "\n";

    int pasos = 0;
    while (simulador.esta_ejecutando() && pasos < 10) {
        cout << "Paso " << (pasos + 1) << ": ";
        simulador.siguiente_paso();
        cout << "Ejecutado\n";
        pasos++;
    }

    cout << "4. Estado final:\n" << simulador.obtener_estado();
    cout << "=== FIN DE LA PRUEBA ===\n";
    return 0;
}
