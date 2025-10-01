#pragma once
#include "tipos.hpp"
#include <vector>
#include <string>
using namespace std;

class CPU;
class Memoria;
class JerarquiaCache;

class Debugger {
public:
    std::vector<AccionDebug> acciones;

    void mov(const std::string& registro, Numero anterior, Numero nuevo);
    void operacion(const std::string& tipo, const std::string& registro, Numero resultado);
    void memoria(const std::string& tipo, Direccion direccion, Numero valor);
    void pila(const std::string& tipo, Numero valor);
    void salto(Direccion origen, Direccion destino);
    void bandera(const std::string& nombre, bool anterior, bool nuevo);
    void limpiar();
    static string estado_registros(const CPU& cpu);
    [[nodiscard]] string ultima_accion() const;
    [[nodiscard]] string historial() const;
};