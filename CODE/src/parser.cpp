#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

Registro Parser::buscar_registro(const string& registro) {
    static const std::unordered_map<string, Registro> registros = {
        {"EAX", Registro::EAX}, {"eax", Registro::EAX},
        {"EBX", Registro::EBX}, {"ebx", Registro::EBX},
        {"ECX", Registro::ECX}, {"ecx", Registro::ECX},
        {"EDX", Registro::EDX}, {"edx", Registro::EDX},
        {"ESP", Registro::ESP}, {"esp", Registro::ESP},
        {"EBP", Registro::EBP}, {"ebp", Registro::EBP},
        {"ESI", Registro::ESI}, {"esi", Registro::ESI},
        {"EDI", Registro::EDI}, {"edi", Registro::EDI}
    };

    if (const auto it = registros.find(registro); it != registros.end())
        return it->second;

    return Registro::EAX;
}

bool Parser::es_numero(const string& texto) {
    return !texto.empty() && std::ranges::all_of(texto, ::isdigit);
}

void Parser::procesar_operandos_binarios(InstruccionPrograma& instruccion, istringstream& iss) {
    string operando1, operando2;
    iss >> operando1 >> operando2;

    if (!operando1.empty() && operando1.back() == ',') operando1.pop_back();

    instruccion.registro_destino = buscar_registro(operando1);

    if (es_numero(operando2)) {
        instruccion.usar_numero_inmediato = true;
        instruccion.numero_inmediato = std::stoi(operando2);
    }
    else
        instruccion.registro_origen = buscar_registro(operando2);
}

void Parser::procesar_operandos_memoria(InstruccionPrograma& instruccion, istringstream& iss, bool es_load) {
    string registro, direccion;
    iss >> registro >> direccion;

    if (!registro.empty() && registro.back() == ',') registro.pop_back();

    if (es_load) instruccion.registro_destino = buscar_registro(registro);
    else instruccion.registro_origen = buscar_registro(registro);

    instruccion.usar_direccion_memoria = true;
    instruccion.direccion_memoria = std::stoi(direccion);
}

InstruccionPrograma Parser::analizar_linea(const string& linea) {
    InstruccionPrograma instruccion;

    if (linea.empty() || linea[0] == ';') return instruccion;

    std::istringstream iss(linea);
    string comando;
    iss >> comando;

    std::ranges::transform(comando, comando.begin(), ::toupper);

    if (comando == "MOV") {
        instruccion.tipo = Comando::MOV;
        procesar_operandos_binarios(instruccion, iss);
    }
    else if (comando == "ADD") {
        instruccion.tipo = Comando::ADD;
        procesar_operandos_binarios(instruccion, iss);
    }
    else if (comando == "SUB") {
        instruccion.tipo = Comando::SUB;
        procesar_operandos_binarios(instruccion, iss);
    }
    else if (comando == "JMP") {
        instruccion.tipo = Comando::JMP;
        string destino;
        iss >> destino;
        instruccion.usar_numero_inmediato = true;
        instruccion.numero_inmediato = std::stoi(destino);
    }
    else if (comando == "LOAD") {
        instruccion.tipo = Comando::LOAD;
        procesar_operandos_memoria(instruccion, iss, true);
    }
    else if (comando == "STORE") {
        instruccion.tipo = Comando::STORE;
        procesar_operandos_memoria(instruccion, iss, false);
    }

    return instruccion;
}

vector<InstruccionPrograma> Parser::cargar_programa(const string& nombre_archivo) {
    vector<InstruccionPrograma> programa;
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open()) return programa;

    string linea;
    while (std::getline(archivo, linea)) {
        linea.erase(0, linea.find_first_not_of(" \t"));
        linea.erase(linea.find_last_not_of(" \t") + 1);

        if (!linea.empty()) programa.push_back(analizar_linea(linea));
    }

    return programa;
}
