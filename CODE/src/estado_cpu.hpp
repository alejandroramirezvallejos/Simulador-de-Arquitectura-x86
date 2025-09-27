#pragma once
#include "../include/tipos.hpp"

class EstadoCPU {
public:
    Palabra obtener_registro(Registro registro) const;
    void establecer_registro(Registro registro, Palabra valor);

    Palabra obtener_pc() const;
    void establecer_pc(Palabra pc);

    bool obtener_bandera(Bandera bandera) const;
    void establecer_bandera(Bandera bandera, bool valor);
};
