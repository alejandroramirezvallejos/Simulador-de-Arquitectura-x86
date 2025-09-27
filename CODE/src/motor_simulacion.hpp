#pragma once
#include "../include/tipos.hpp"
#include "parser.hpp"
#include "estado_cpu.hpp"
#include "memoria.hpp"
#include <vector>
#include <string>

class MotorSimulacion {
private:
    EstadoCPU cpu;
    Memoria memoria;
    std::vector<InstruccionPrograma> programa;
    bool ejecutando;

public:
    MotorSimulacion();

    void cargar_programa(const std::string& nombre_archivo);
    void paso();
    std::string obtener_estado() const;
    void reiniciar();
    bool esta_ejecutando() const;
};
