#pragma once
#include "parser.hpp"
#include "cpu.hpp"
#include "memoria.hpp"
#include <vector>
#include <string>

using std::string;
using std::vector;

class MotorSimulacion {
    public:
        CPU cpu;
        Memoria memoria;
        vector<InstruccionPrograma> programa;
        bool ejecutando{false};

        MotorSimulacion();
        void cargar_programa(const string& nombre_archivo);
        void siguiente_paso();
        [[nodiscard]] string obtener_estado() const;
        void reiniciar();
        [[nodiscard]] bool esta_ejecutando() const;

    private:
        void ejecutarInstruccion(const InstruccionPrograma& instruccion);
        void ejecutarMov(const InstruccionPrograma& instruccion);
        void ejecutarAdd(const InstruccionPrograma& instruccion);
        void ejecutarSub(const InstruccionPrograma& instruccion);
        void ejecutarJmp(const InstruccionPrograma& instruccion);
        void ejecutarLoad(const InstruccionPrograma& instruccion);
        void ejecutarStore(const InstruccionPrograma& instruccion);
};
