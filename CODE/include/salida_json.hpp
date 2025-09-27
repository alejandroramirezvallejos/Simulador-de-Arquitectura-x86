#pragma once
#include <string>

class EstadoCPU;
class Memoria;

namespace SalidaJson {
    std::string serializar_estado(const EstadoCPU& cpu, const Memoria& memoria);
    void escribir_estado(const EstadoCPU& cpu, const Memoria& memoria, const std::string& nombre_archivo);
};
