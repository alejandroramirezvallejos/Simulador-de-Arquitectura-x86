#pragma once
#include "../include/tipos.hpp"
#include <string>
#include <vector>

struct InstruccionPrograma {
    Instruccion tipo;
    Registro registro_destino;
    Registro registro_origen;
    Palabra valor_inmediato;
    Direccion direccion_memoria;
    bool usar_valor_inmediato;
    bool usar_direccion_memoria;

    InstruccionPrograma();
};

class Parser {
public:
    static InstruccionPrograma analizar_linea(const std::string& linea);
    static std::vector<InstruccionPrograma> cargar_programa(const std::string& archivo);
};
