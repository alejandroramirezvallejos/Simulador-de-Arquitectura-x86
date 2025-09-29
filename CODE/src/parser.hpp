#pragma once
#include "../include/tipos.hpp"
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::istringstream;

struct InstruccionPrograma {
    Comando tipo{Comando::NOP};
    Registro registro_destino{Registro::EAX};
    Registro registro_origen{Registro::EAX};
    Numero numero_inmediato{};
    Direccion direccion_memoria{};
    bool usar_numero_inmediato{false};
    bool usar_direccion_memoria{false};

    InstruccionPrograma() = default;
};

class Parser {
    public:
        [[nodiscard]] static Registro buscar_registro(const string& registro);
        [[nodiscard]] static InstruccionPrograma analizar_linea(const string& linea);
        [[nodiscard]] static vector<InstruccionPrograma> cargar_programa(const string& nombre_archivo);

    private:
        [[nodiscard]] static bool es_numero(const string& texto);
        static void procesar_operandos_binarios(InstruccionPrograma& instruccion, istringstream& iss);
        static void procesar_operandos_memoria(InstruccionPrograma& instruccion, istringstream& iss, bool es_load);
};
