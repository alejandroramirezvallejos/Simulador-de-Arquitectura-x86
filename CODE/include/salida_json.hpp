#pragma once
#include <string>
using namespace std;

class CPU;
class Memoria;

namespace SalidaJson {
    string serializar_estado(const CPU& cpu, const Memoria& memoria);
    void escribir_estado(const CPU& cpu, const Memoria& memoria, const std::string& nombre_archivo);
};
