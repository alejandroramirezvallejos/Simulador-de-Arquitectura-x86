#include "../include/salida_json.hpp"
#include "cpu.hpp"
#include "memoria.hpp"
#include "jerarquia_cache.hpp"
#include <sstream>
#include <fstream>

namespace {
    string registros_interno(const CPU& cpu) {
        ostringstream json;

        json << "  \"registros_x64\": {\n";
        json << "    \"RAX\": " << cpu.obtener_registro(Registro::RAX) << ",\n";
        json << "    \"RBX\": " << cpu.obtener_registro(Registro::RBX) << ",\n";
        json << "    \"RCX\": " << cpu.obtener_registro(Registro::RCX) << ",\n";
        json << "    \"RDX\": " << cpu.obtener_registro(Registro::RDX) << ",\n";
        json << "    \"RSP\": " << cpu.obtener_registro(Registro::RSP) << ",\n";
        json << "    \"RBP\": " << cpu.obtener_registro(Registro::RBP) << ",\n";
        json << "    \"RSI\": " << cpu.obtener_registro(Registro::RSI) << ",\n";
        json << "    \"RDI\": " << cpu.obtener_registro(Registro::RDI) << ",\n";
        json << "    \"R8\": " << cpu.obtener_registro(Registro::R8) << ",\n";
        json << "    \"R9\": " << cpu.obtener_registro(Registro::R9) << ",\n";
        json << "    \"R10\": " << cpu.obtener_registro(Registro::R10) << ",\n";
        json << "    \"R11\": " << cpu.obtener_registro(Registro::R11) << ",\n";
        json << "    \"R12\": " << cpu.obtener_registro(Registro::R12) << ",\n";
        json << "    \"R13\": " << cpu.obtener_registro(Registro::R13) << ",\n";
        json << "    \"R14\": " << cpu.obtener_registro(Registro::R14) << ",\n";
        json << "    \"R15\": " << cpu.obtener_registro(Registro::R15) << ",\n";
        json << "    \"RIP\": " << cpu.obtener_registro(Registro::RIP) << "\n";
        json << "  },\n";
        json << "  \"registros_internos\": {\n";
        json << "    \"RIM\": " << cpu.obtener_registro_interno(RegistroInterno::RIM) << ",\n";
        json << "    \"RMD\": " << cpu.obtener_registro_interno(RegistroInterno::RMD) << ",\n";
        json << "    \"RI\": " << cpu.obtener_registro_interno(RegistroInterno::RI) << ",\n";
        json << "    \"REN1\": " << cpu.obtener_registro_interno(RegistroInterno::REN1) << ",\n";
        json << "    \"REN2\": " << cpu.obtener_registro_interno(RegistroInterno::REN2) << ",\n";
        json << "    \"ACUMULADOR\": " << cpu.obtener_registro_interno(RegistroInterno::ACUMULADOR) << ",\n";
        json << "    \"RESTADOR\": " << cpu.obtener_registro_interno(RegistroInterno::RESTADOR) << ",\n";
        json << "    \"SECUENCIADOR\": " << cpu.obtener_registro_interno(RegistroInterno::SECUENCIADOR) << "\n";
        json << "  }";

        return json.str();
    }

    string cpu_interno(const CPU& cpu) {
        ostringstream json;

        json << registros_interno(cpu) << ",\n";
        json << "  \"contador\": " << cpu.obtener_contador() << ",\n";
        json << "  \"banderas\": {\n";
        json << "    \"cero\": " << (cpu.obtener_bandera(Bandera::CERO) ? "true" : "false") << ",\n";
        json << "    \"acarreo\": " << (cpu.obtener_bandera(Bandera::ACARREO) ? "true" : "false") << ",\n";
        json << "    \"signo\": " << (cpu.obtener_bandera(Bandera::SIGNO) ? "true" : "false") << ",\n";
        json << "  }";

        return json.str();
    }

    string memoria_interno(const Memoria& memoria) {
        ostringstream json;
        json << "  \"memoria\": {\n";
        json << "    \"total_numeros_64bit\": " << (1024 / 8) << ",\n";
        json << "    \"todos_los_numeros\": [\n";

        for (int i = 0; i < 128; ++i) {
            json << "      " << memoria.leer_numero(i * 8);
            if (i < 127) json << ",";
            json << "\n";
        }

        json << "    ]\n";
        json << "  }";

        return json.str();
    }

    string caches_interno(const JerarquiaCache& caches) {
        ostringstream json;

        json << "  \"caches\": {\n";
        json << "    \"L1\": {\n";
        json << "      \"hits\": " << caches.cache_l1.calcular_aciertos() << ",\n";
        json << "      \"misses\": " << caches.cache_l1.calcular_fallos() << ",\n";
        json << "      \"tamaño\": " << caches.cache_l1.tamaño << "\n";
        json << "    },\n";
        json << "    \"L2\": {\n";
        json << "      \"hits\": " << caches.cache_l2.calcular_aciertos() << ",\n";
        json << "      \"misses\": " << caches.cache_l2.calcular_fallos() << ",\n";
        json << "      \"tamaño\": " << caches.cache_l2.tamaño << "\n";
        json << "    },\n";
        json << "    \"L3\": {\n";
        json << "      \"hits\": " << caches.cache_l3.calcular_aciertos() << ",\n";
        json << "      \"misses\": " << caches.cache_l3.calcular_fallos() << ",\n";
        json << "      \"tamaño\": " << caches.cache_l3.tamaño << "\n";
        json << "    }\n";
        json << "  }";

        return json.str();
    }
}

string SalidaJson::registros(const CPU& cpu) {
    ostringstream json;
    json << "{\n" << registros_interno(cpu) << "\n}";
    return json.str();
}

string SalidaJson::memoria(const Memoria& memoria) {
    ostringstream json;
    json << "{\n" << memoria_interno(memoria) << "\n}";
    return json.str();
}

string SalidaJson::caches(const JerarquiaCache& caches) {
    ostringstream json;
    json << "{\n" << caches_interno(caches) << "\n}";
    return json.str();
}

string SalidaJson::estado(const CPU& cpu, const Memoria& memoria, const JerarquiaCache& caches) {
    ostringstream json;

    json << "{\n";
    json << cpu_interno(cpu) << ",\n";
    json << memoria_interno(memoria) << ",\n";
    json << caches_interno(caches) << "\n";
    json << "}";

    return json.str();
}

void SalidaJson::escribir(const CPU& cpu, const Memoria& memoria, const string& archivo) {
    if (ofstream file(archivo); file.is_open()) {
        file << "{\n" << cpu_interno(cpu) << ",\n" << memoria_interno(memoria) << "\n}";
    }
}
