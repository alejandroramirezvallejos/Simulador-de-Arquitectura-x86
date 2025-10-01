#pragma once
#include "parser.hpp"
#include "cpu.hpp"
#include "memoria.hpp"
#include "jerarquia_cache.hpp"
#include "../include/debugger.hpp"
#include <vector>
#include <string>
using std::string;
using std::vector;

class MotorSimulacion {
    public:
        CPU cpu;
        Memoria memoria;
        JerarquiaCache caches{};
        Debugger debugger;
        vector<InstruccionPrograma> programa;
        bool ejecutando{false};

        MotorSimulacion() = default;

        void cargar_programa(const string& nombre_archivo);
        void siguiente_paso();
        void reiniciar();
        void limpiar_debug();
        [[nodiscard]] string obtener_estado() const;
        [[nodiscard]] string obtener_estado_con_caches() const;
        [[nodiscard]] bool esta_ejecutando() const;
        [[nodiscard]] string obtener_debug_info() const;
        [[nodiscard]] string obtener_registros_internos() const;
        [[nodiscard]] string obtener_historial_debug() const;
        [[nodiscard]] string obtener_selector_memoria() const;
        [[nodiscard]] string obtener_memoria() const;

    private:
        string ultima_fuente{"RAM"};

        void ejecutarInstruccion(const InstruccionPrograma& instruccion);
        void ejecutarMovq(const InstruccionPrograma& instruccion);
        void ejecutarMovl(const InstruccionPrograma& instruccion);
        void ejecutarAddq(const InstruccionPrograma& instruccion);
        void ejecutarAddl(const InstruccionPrograma& instruccion);
        void ejecutarSubq(const InstruccionPrograma& instruccion);
        void ejecutarSubl(const InstruccionPrograma& instruccion);
        void ejecutarPushq(const InstruccionPrograma& instruccion);
        void ejecutarPopq(const InstruccionPrograma& instruccion);
        void ejecutarJmp(const InstruccionPrograma& instruccion);
        void ejecutarLoad(const InstruccionPrograma& instruccion);
        void ejecutarStore(const InstruccionPrograma& instruccion);
        void actualizar_banderas(Numero resultado, Numero operando1, Numero operando2);
        static string obtener_registro(Registro registro) ;
};
