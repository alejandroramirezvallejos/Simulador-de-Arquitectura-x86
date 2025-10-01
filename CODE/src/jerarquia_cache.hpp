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

        Numero leer(Direccion direccion, const class Memoria& memoria) const;
        void escribir(Direccion direccion, Numero dato, Memoria& memoria) const;
        void invalidar_todos() const;
        [[nodiscard]] string obtener_estadisticas() const;
        [[nodiscard]] bool contiene(Direccion direccion) const;
};
