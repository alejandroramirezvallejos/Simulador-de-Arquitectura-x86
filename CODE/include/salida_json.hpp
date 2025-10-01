#pragma once
#include <string>
using namespace std;

class CPU;
class Memoria;
class JerarquiaCache;

namespace SalidaJson {
    string registros(const CPU& cpu);
    string memoria(const Memoria& memoria);
    string caches(const JerarquiaCache& caches);
    string estado(const CPU& cpu, const Memoria& memoria, const JerarquiaCache& caches);
    void escribir(const CPU& cpu, const Memoria& memoria, const string& archivo);
};
