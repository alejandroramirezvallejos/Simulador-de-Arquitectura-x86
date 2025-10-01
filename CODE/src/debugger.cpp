#include "../include/debugger.hpp"
#include "cpu.hpp"
#include "jerarquia_cache.hpp"
#include <sstream>

void Debugger::mov(const string& registro, const Numero anterior, const Numero nuevo) {
    AccionDebug accion;
    accion.tipo_instruccion = "MOV";
    accion.descripcion = "MOV " + registro + ": " + std::to_string(anterior) + " -> " + std::to_string(nuevo);
    accion.registro_afectado = registro;
    accion.valor_anterior = anterior;
    accion.valor_nuevo = nuevo;
    acciones.push_back(accion);
}

void Debugger::operacion(const string& tipo, const std::string& registro, const Numero resultado) {
    AccionDebug accion;
    accion.tipo_instruccion = tipo;
    accion.descripcion = tipo + " " + registro + " = " + std::to_string(resultado);
    accion.registro_afectado = registro;
    accion.valor_nuevo = resultado;
    acciones.push_back(accion);
}

void Debugger::memoria(const string& tipo, const Direccion direccion, const Numero valor) {
    AccionDebug accion;
    accion.tipo_instruccion = tipo;
    accion.descripcion = tipo + " [" + std::to_string(direccion) + "] = " + std::to_string(valor);
    accion.direccion_memoria = direccion;
    accion.valor_nuevo = valor;
    acciones.push_back(accion);
}

void Debugger::pila(const string& tipo, const Numero valor) {
    AccionDebug accion;
    accion.tipo_instruccion = tipo;
    accion.descripcion = tipo + " " + std::to_string(valor);
    accion.valor_nuevo = valor;
    acciones.push_back(accion);
}

void Debugger::salto(const Direccion origen, const Direccion destino) {
    AccionDebug accion;
    accion.tipo_instruccion = "JMP";
    accion.descripcion = "JMP " + std::to_string(origen) + " -> " + std::to_string(destino);
    accion.valor_anterior = origen;
    accion.valor_nuevo = destino;
    acciones.push_back(accion);
}

void Debugger::bandera(const string& nombre, const bool anterior, const bool nuevo) {
    AccionDebug accion;
    accion.tipo_instruccion = "FLAG";
    accion.descripcion = nombre + ": " + (anterior ? "1" : "0") + " -> " + (nuevo ? "1" : "0");
    accion.valor_anterior = anterior ? 1 : 0;
    accion.valor_nuevo = nuevo ? 1 : 0;
    acciones.push_back(accion);
}

string Debugger::ultima_accion() const {
    if (acciones.empty()) return "{}";

    const auto& ultima = acciones.back();
    return R"({"tipo":")" + ultima.tipo_instruccion + R"(","desc":")" + ultima.descripcion + "\"}";
}

string Debugger::historial() const {
    if (acciones.empty()) return "[]";

    ostringstream json;
    json << "[";

    for (size_t i = 0; i < acciones.size(); ++i) {
        json << "{\"paso\":" << (i + 1) << R"(,"desc":")" << acciones[i].descripcion << "\"}";
        if (i < acciones.size() - 1) json << ",";
    }

    json << "]";

    return json.str();
}

string Debugger::estado_registros(const CPU& cpu) {
    ostringstream json;

    json << "{";
    json << "\"RAX\":" << cpu.obtener_registro(Registro::RAX) << ",";
    json << "\"RBX\":" << cpu.obtener_registro(Registro::RBX) << ",";
    json << "\"RCX\":" << cpu.obtener_registro(Registro::RCX) << ",";
    json << "\"RDX\":" << cpu.obtener_registro(Registro::RDX);
    json << "}";

    return json.str();
}

void Debugger::limpiar() {
    acciones.clear();
}
