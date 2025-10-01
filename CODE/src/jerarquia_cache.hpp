#pragma once
#include "../include/tipos.hpp"
#include "cache.hpp"
#include <string>
using std::string;

class JerarquiaCache {
    public:
        Cache cache_l1;
        Cache cache_l2;
        Cache cache_l3;

        JerarquiaCache();

        Numero leer(Direccion direccion, const class Memoria& memoria);
        void escribir(Direccion direccion, Numero dato, Memoria& memoria);
        void invalidar_todos();

        [[nodiscard]] string obtener_estadisticas() const;
};
