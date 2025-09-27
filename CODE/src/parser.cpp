#include "parser.hpp"

InstruccionPrograma::InstruccionPrograma() {
    tipo = Instruccion::NOP;
    registro_destino = Registro::EAX;
    registro_origen = Registro::EAX;
    valor_inmediato = 0;
    direccion_memoria = 0;
    usar_valor_inmediato = false;
    usar_direccion_memoria = false;
}

InstruccionPrograma Parser::analizar_linea(const std::string& linea) {
    InstruccionPrograma instruccion;

    if (linea.empty()) return instruccion;

    if (linea.find("MOV") != std::string::npos)
        instruccion.tipo = Instruccion::MOV;

    else if (linea.find("ADD") != std::string::npos)
        instruccion.tipo = Instruccion::ADD;

    else if (linea.find("SUB") != std::string::npos)
        instruccion.tipo = Instruccion::SUB;

    else if (linea.find("JMP") != std::string::npos)
        instruccion.tipo = Instruccion::JMP;

    else if (linea.find("LOAD") != std::string::npos)
        instruccion.tipo = Instruccion::LOAD;

    else if (linea.find("STORE") != std::string::npos)
        instruccion.tipo = Instruccion::STORE;

    return instruccion;
}

std::vector<InstruccionPrograma> Parser::cargar_programa(const std::string& archivo) {
    std::vector<InstruccionPrograma> programa;
    return programa;
}
