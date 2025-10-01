#include "jerarquia_cache.hpp"
#include "memoria.hpp"
#include <sstream>

JerarquiaCache::JerarquiaCache() : cache_l1(4, "L1"), cache_l2(8, "L2"), cache_l3(16, "L3") {}

Numero JerarquiaCache::leer(const Direccion direccion, const Memoria& memoria) const {
    Numero dato;

    if (cache_l1.buscar(direccion, dato)) return dato;

    if (cache_l2.buscar(direccion, dato)) {
        cache_l1.escribir(direccion, dato);
        return dato;
    }

    if (cache_l3.buscar(direccion, dato)) {
        cache_l2.escribir(direccion, dato);
        cache_l1.escribir(direccion, dato);

        return dato;
    }

    dato = memoria.leer_numero(direccion);
    cache_l3.escribir(direccion, dato);
    cache_l2.escribir(direccion, dato);
    cache_l1.escribir(direccion, dato);

    return dato;
}

void JerarquiaCache::escribir(const Direccion direccion, const Numero dato, Memoria& memoria) const {
    memoria.escribir_numero(direccion, dato);
    cache_l1.escribir(direccion, dato);
    cache_l2.escribir(direccion, dato);
    cache_l3.escribir(direccion, dato);
}

void JerarquiaCache::invalidar_todos() const {
    cache_l1.invalidar();
    cache_l2.invalidar();
    cache_l3.invalidar();
}

string JerarquiaCache::obtener_estadisticas() const {
    std::ostringstream estadisticas;

    estadisticas << "Cache L1: " << cache_l1.calcular_aciertos() << " hits, "
          << cache_l1.calcular_fallos() << " misses\n";
    estadisticas << "Cache L2: " << cache_l2.calcular_aciertos() << " hits, "
          << cache_l2.calcular_fallos() << " misses\n";
    estadisticas << "Cache L3: " << cache_l3.calcular_aciertos() << " hits, "
          << cache_l3.calcular_fallos() << " misses\n";

    return estadisticas.str();
}

bool JerarquiaCache::contiene(const Direccion direccion) const {
    Numero cache_ficticia;

    return cache_l1.buscar(direccion, cache_ficticia) ||
           cache_l2.buscar(direccion, cache_ficticia) ||
           cache_l3.buscar(direccion, cache_ficticia);
}
