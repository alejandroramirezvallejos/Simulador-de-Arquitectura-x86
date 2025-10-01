#pragma once
#include "../include/tipos.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::istringstream;

struct InstruccionPrograma {
    Comando tipo{Comando::NOP};
    Registro registro_destino{Registro::RAX};
    Registro registro_origen{Registro::RAX};
    Numero numero_inmediato{};
    Direccion direccion_memoria{};
    bool usar_numero_inmediato{false};
    bool usar_direccion_memoria{false};

    InstruccionPrograma() = default;
};

class Parser {
    public:
        static Registro buscar_registro(const string& registro);
        static InstruccionPrograma analizar_linea(const string& linea);
        static vector<InstruccionPrograma> cargar_programa(const string& nombre_archivo);

    private:
        static string limpiar_sintaxis(const string& linea);
        static bool es_direccion_memoria(const string& operando);
        static void procesar_direccion_memoria(const string& operando, InstruccionPrograma& instruccion);
        static void procesar_operandos(InstruccionPrograma& instruccion, istringstream& iss);
        static bool es_valor_inmediato(const string& operando);
        static string limpiar_valor_inmediato(const string& operando);
};
