#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

Registro Parser::buscar_registro(const string& registro) {
    static const std::unordered_map<string, Registro> registros = {
        {"RAX", Registro::RAX}, {"rax", Registro::RAX}, {"%rax", Registro::RAX},
        {"RBX", Registro::RBX}, {"rbx", Registro::RBX}, {"%rbx", Registro::RBX},
        {"RCX", Registro::RCX}, {"rcx", Registro::RCX}, {"%rcx", Registro::RCX},
        {"RDX", Registro::RDX}, {"rdx", Registro::RDX}, {"%rdx", Registro::RDX},
        {"RSP", Registro::RSP}, {"rsp", Registro::RSP}, {"%rsp", Registro::RSP},
        {"RBP", Registro::RBP}, {"rbp", Registro::RBP}, {"%rbp", Registro::RBP},
        {"RSI", Registro::RSI}, {"rsi", Registro::RSI}, {"%rsi", Registro::RSI},
        {"RDI", Registro::RDI}, {"rdi", Registro::RDI}, {"%rdi", Registro::RDI},
        {"R8",  Registro::R8},  {"r8",  Registro::R8},  {"%r8",  Registro::R8},
        {"R9",  Registro::R9},  {"r9",  Registro::R9},  {"%r9",  Registro::R9},
        {"R10", Registro::R10}, {"r10", Registro::R10}, {"%r10", Registro::R10},
        {"R11", Registro::R11}, {"r11", Registro::R11}, {"%r11", Registro::R11},
        {"R12", Registro::R12}, {"r12", Registro::R12}, {"%r12", Registro::R12},
        {"R13", Registro::R13}, {"r13", Registro::R13}, {"%r13", Registro::R13},
        {"R14", Registro::R14}, {"r14", Registro::R14}, {"%r14", Registro::R14},
        {"R15", Registro::R15}, {"r15", Registro::R15}, {"%r15", Registro::R15},
        {"RIP", Registro::RIP}, {"rip", Registro::RIP}, {"%rip", Registro::RIP},
        {"EAX", Registro::RAX}, {"eax", Registro::RAX}, {"%eax", Registro::RAX},
        {"EBX", Registro::RBX}, {"ebx", Registro::RBX}, {"%ebx", Registro::RBX},
        {"ECX", Registro::RCX}, {"ecx", Registro::RCX}, {"%ecx", Registro::RCX},
        {"EDX", Registro::RDX}, {"edx", Registro::RDX}, {"%edx", Registro::RDX},
        {"ESP", Registro::RSP}, {"esp", Registro::RSP}, {"%esp", Registro::RSP},
        {"EBP", Registro::RBP}, {"ebp", Registro::RBP}, {"%ebp", Registro::RBP},
        {"ESI", Registro::RSI}, {"esi", Registro::RSI}, {"%esi", Registro::RSI},
        {"EDI", Registro::RDI}, {"edi", Registro::RDI}, {"%edi", Registro::RDI}
    };

    string registro_limpio = registro;
    if (!registro_limpio.empty() && registro_limpio[0] == '%')
        registro_limpio = registro_limpio.substr(1);

    const auto it = registros.find(registro_limpio);
    return (it != registros.end()) ? it->second : Registro::RAX;
}

string Parser::limpiar_sintaxis(const string& linea) {
    string resultado = linea;

    if (const size_t pos = resultado.find('#'); pos != string::npos)
        resultado = resultado.substr(0, pos);

    if (const size_t pos = resultado.find(';'); pos != string::npos)
        resultado = resultado.substr(0, pos);

    string limpio;
    bool espacio_anterior = false;
    for (char c : resultado) {
        if (c == '\t') c = ' ';
        if (c == ' ') {
            if (!espacio_anterior) limpio += c;
            espacio_anterior = true;
        } else {
            limpio += c;
            espacio_anterior = false;
        }
    }

    if (!limpio.empty() && limpio.front() == ' ') limpio.erase(0, 1);
    if (!limpio.empty() && limpio.back() == ' ') limpio.pop_back();

    return limpio;
}

bool Parser::es_direccion_memoria(const string& operando) {
    return operando.find('(') != string::npos && operando.find(')') != string::npos;
}

void Parser::procesar_direccion_memoria(const string& operando, InstruccionPrograma& instruccion) {
    const size_t pos_parentesis = operando.find('(');
    const size_t pos_cierre = operando.find(')');

    if (pos_parentesis == string::npos || pos_cierre == string::npos) return;

    const string offset_str = operando.substr(0, pos_parentesis);
    const string registro_str = operando.substr(pos_parentesis + 1, pos_cierre - pos_parentesis - 1);

    instruccion.registro_origen = buscar_registro(registro_str);
    instruccion.usar_direccion_memoria = true;

    if (!offset_str.empty()) {
        int offset = 0;
        if (offset_str.starts_with("0x") || offset_str.starts_with("0X"))
            offset = std::stoi(offset_str, nullptr, 16);
        else
            offset = std::stoi(offset_str);
        instruccion.direccion_memoria = static_cast<Direccion>(offset);
    }
    else instruccion.direccion_memoria = 0;
}

bool Parser::es_valor_inmediato(const string& operando) {
    return !operando.empty() && operando[0] == '$';
}

string Parser::limpiar_valor_inmediato(const string& operando) {
    if (operando.empty() || operando[0] != '$') return operando;

    string valor = operando.substr(1);

    if (valor.starts_with("0x") || valor.starts_with("0X"))
        return std::to_string(std::stoi(valor, nullptr, 16));

    return valor;
}

void Parser::procesar_operandos(InstruccionPrograma& instruccion, istringstream& iss) {
    string operando1;
    iss >> operando1;

    if (!operando1.empty() && operando1.back() == ',')
        operando1.pop_back();

    if (string operando2; iss >> operando2) {
        if (es_valor_inmediato(operando1)) {
            instruccion.usar_numero_inmediato = true;
            instruccion.numero_inmediato = std::stoll(limpiar_valor_inmediato(operando1));
        }
        else if (es_direccion_memoria(operando1))
            procesar_direccion_memoria(operando1, instruccion);
        else
            instruccion.registro_origen = buscar_registro(operando1);

        if (es_direccion_memoria(operando2))
            procesar_direccion_memoria(operando2, instruccion);
        else
            instruccion.registro_destino = buscar_registro(operando2);
    }
    else {
        if (es_valor_inmediato(operando1)) {
            instruccion.usar_numero_inmediato = true;
            instruccion.numero_inmediato = std::stoll(limpiar_valor_inmediato(operando1));
        }
        else if (es_direccion_memoria(operando1))
            procesar_direccion_memoria(operando1, instruccion);
        else {
            if (instruccion.tipo == Comando::POPQ)
                instruccion.registro_destino = buscar_registro(operando1);
            else
                instruccion.registro_origen = buscar_registro(operando1);
        }
    }
}

InstruccionPrograma Parser::analizar_linea(const string& linea) {
    InstruccionPrograma instruccion;

    if (linea.empty() || linea[0] == ';' || linea[0] == '#') return instruccion;

    const string linea_limpia = limpiar_sintaxis(linea);
    if (linea_limpia.empty()) return instruccion;

    std::istringstream iss(linea_limpia);
    string comando;
    iss >> comando;

    std::ranges::transform(comando, comando.begin(), ::toupper);

    if (comando == "MOVQ" || comando == "MOV") {
        instruccion.tipo = Comando::MOVQ;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "MOVL") {
        instruccion.tipo = Comando::MOVL;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "ADDQ" || comando == "ADD") {
        instruccion.tipo = Comando::ADDQ;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "ADDL") {
        instruccion.tipo = Comando::ADDL;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "SUBQ" || comando == "SUB") {
        instruccion.tipo = Comando::SUBQ;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "SUBL") {
        instruccion.tipo = Comando::SUBL;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "PUSHQ" || comando == "PUSH") {
        instruccion.tipo = Comando::PUSHQ;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "POPQ" || comando == "POP") {
        instruccion.tipo = Comando::POPQ;
        procesar_operandos(instruccion, iss);
    }
    else if (comando == "JMP") {
        instruccion.tipo = Comando::JMP;
        procesar_operandos(instruccion, iss);
    }

    return instruccion;
}

vector<InstruccionPrograma> Parser::cargar_programa(const string& nombre_archivo) {
    vector<InstruccionPrograma> programa;
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open()) return programa;

    string linea;
    while (std::getline(archivo, linea)) {
        if (const auto instruccion = analizar_linea(linea); instruccion.tipo != Comando::NOP)
            programa.push_back(instruccion);
    }

    return programa;
}
