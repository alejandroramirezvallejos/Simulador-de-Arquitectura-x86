#include "../include/salida_json.hpp"
#include "cpu.hpp"
#include "memoria.hpp"
#include <sstream>
#include <fstream>

string SalidaJson::serializar_estado(const CPU& cpu, const Memoria& memoria) {
    ostringstream json;

    json << "{\n";
    json << "  \"registros\": {\n";
    json << "    \"EAX\": " << cpu.obtener_registro(Registro::EAX) << ",\n";
    json << "    \"EBX\": " << cpu.obtener_registro(Registro::EBX) << ",\n";
    json << "    \"ECX\": " << cpu.obtener_registro(Registro::ECX) << ",\n";
    json << "    \"EDX\": " << cpu.obtener_registro(Registro::EDX) << "\n";
    json << "  },\n";
    json << "  \"contador\": " << cpu.obtener_contador() << ",\n";
    json << "  \"banderas\": {\n";
    json << "    \"cero\": " << (cpu.obtener_bandera(Bandera::CERO) ? "true" : "false") << ",\n";
    json << "    \"acarreo\": " << (cpu.obtener_bandera(Bandera::ACARREO) ? "true" : "false") << "\n";
    json << "  },\n";
    json << "  \"memoria\": {\n";
    json << "    \"total_numeros\": " << (1024 / 4) << ",\n";
    json << "    \"todos_los_numeros\": [\n";

    for (int i = 0; i < 256; ++i) {
        json << "      " << memoria.leer_numero(i * 4);
        if (i < 255) json << ",";
        json << "\n";
    }

    json << "    ]\n";
    json << "  }\n";
    json << "}";

    return json.str();
}

void SalidaJson::escribir_estado(const CPU& cpu, const Memoria& memoria, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo);

    if (archivo.is_open()) {
        archivo << serializar_estado(cpu, memoria);
        archivo.close();
    }
}
