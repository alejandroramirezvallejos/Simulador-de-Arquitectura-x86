#pragma once
#include <string>
using namespace std;

class CPU;
class Memoria;
class JerarquiaCache;

namespace SalidaJson {
    string serializar_registros(const CPU& cpu);
    string serializar_memoria(const Memoria& memoria);
    string serializar_caches(const JerarquiaCache& caches);
    string serializar_estado(const CPU& cpu, const Memoria& memoria);
    string serializar_estado_con_caches(const CPU& cpu, const Memoria& memoria, const JerarquiaCache& caches);
    void escribir_estado(const CPU& cpu, const Memoria& memoria, const string& nombre_archivo);
};
