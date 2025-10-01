#include "../include/salida_json.hpp"
#include "cpu.hpp"
#include "memoria.hpp"
#include "jerarquia_cache.hpp"
#include <sstream>
#include <fstream>

namespace {
    string serializar_registros_interno(const CPU& cpu) {
        ostringstream json;
        json << "  \"registros\": {\n";
        json << "    \"EAX\": " << cpu.obtener_registro(Registro::EAX) << ",\n";
        json << "    \"EBX\": " << cpu.obtener_registro(Registro::EBX) << ",\n";
        json << "    \"ECX\": " << cpu.obtener_registro(Registro::ECX) << ",\n";
        json << "    \"EDX\": " << cpu.obtener_registro(Registro::EDX) << ",\n";
        json << "    \"ESP\": " << cpu.obtener_registro(Registro::ESP) << ",\n";
        json << "    \"EBP\": " << cpu.obtener_registro(Registro::EBP) << ",\n";
        json << "    \"ESI\": " << cpu.obtener_registro(Registro::ESI) << ",\n";
        json << "    \"EDI\": " << cpu.obtener_registro(Registro::EDI) << "\n";
        json << "  }";
        return json.str();
    }

    string serializar_cpu_interno(const CPU& cpu) {
        ostringstream json;
        json << serializar_registros_interno(cpu) << ",\n";
        json << "  \"contador\": " << cpu.obtener_contador() << ",\n";
        json << "  \"banderas\": {\n";
        json << "    \"cero\": " << (cpu.obtener_bandera(Bandera::CERO) ? "true" : "false") << ",\n";
        json << "    \"acarreo\": " << (cpu.obtener_bandera(Bandera::ACARREO) ? "true" : "false") << ",\n";
        json << "    \"signo\": " << (cpu.obtener_bandera(Bandera::SIGNO) ? "true" : "false") << "\n";
        json << "  }";
        return json.str();
    }

    string serializar_memoria_interno(const Memoria& memoria) {
        ostringstream json;
        json << "  \"memoria\": {\n";
        json << "    \"total_numeros\": " << (1024 / 4) << ",\n";
        json << "    \"todos_los_numeros\": [\n";

        for (int i = 0; i < 256; ++i) {
            json << "      " << memoria.leer_numero(i * 4);
            if (i < 255) json << ",";
            json << "\n";
        }

        json << "    ]\n";
        json << "  }";
        return json.str();
    }

    string serializar_caches_interno(const JerarquiaCache& caches) {
        ostringstream json;
        json << "  \"caches\": {\n";
        json << "    \"L1\": {\n";
        json << "      \"hits\": " << caches.cache_l1.calcular_hits() << ",\n";
        json << "      \"misses\": " << caches.cache_l1.calcular_misses() << ",\n";
        json << "      \"tamaño\": " << caches.cache_l1.tamaño << "\n";
        json << "    },\n";
        json << "    \"L2\": {\n";
        json << "      \"hits\": " << caches.cache_l2.calcular_hits() << ",\n";
        json << "      \"misses\": " << caches.cache_l2.calcular_misses() << ",\n";
        json << "      \"tamaño\": " << caches.cache_l2.tamaño << "\n";
        json << "    },\n";
        json << "    \"L3\": {\n";
        json << "      \"hits\": " << caches.cache_l3.calcular_hits() << ",\n";
        json << "      \"misses\": " << caches.cache_l3.calcular_misses() << ",\n";
        json << "      \"tamaño\": " << caches.cache_l3.tamaño << "\n";
        json << "    }\n";
        json << "  }";
        return json.str();
    }
}

string SalidaJson::serializar_registros(const CPU& cpu) {
    ostringstream json;
    json << "{\n" << serializar_registros_interno(cpu) << "\n}";
    return json.str();
}

string SalidaJson::serializar_memoria(const Memoria& memoria) {
    ostringstream json;
    json << "{\n" << serializar_memoria_interno(memoria) << "\n}";
    return json.str();
}

string SalidaJson::serializar_caches(const JerarquiaCache& caches) {
    ostringstream json;
    json << "{\n" << serializar_caches_interno(caches) << "\n}";
    return json.str();
}

string SalidaJson::serializar_estado(const CPU& cpu, const Memoria& memoria) {
    ostringstream json;
    json << "{\n";
    json << serializar_cpu_interno(cpu) << ",\n";
    json << serializar_memoria_interno(memoria) << "\n";
    json << "}";
    return json.str();
}

string SalidaJson::serializar_estado_con_caches(const CPU& cpu, const Memoria& memoria, const JerarquiaCache& caches) {
    ostringstream json;
    json << "{\n";
    json << serializar_cpu_interno(cpu) << ",\n";
    json << serializar_memoria_interno(memoria) << ",\n";
    json << serializar_caches_interno(caches) << "\n";
    json << "}";
    return json.str();
}

void SalidaJson::escribir_estado(const CPU& cpu, const Memoria& memoria, const string& nombre_archivo) {
    if (ofstream archivo(nombre_archivo); archivo.is_open()) {
        archivo << serializar_estado(cpu, memoria);
        archivo.close();
    }
}
