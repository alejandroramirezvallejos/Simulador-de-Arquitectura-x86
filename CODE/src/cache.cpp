#include "cache.hpp"
#include "memoria.hpp"
#include <sstream>
#include <string>
using std::string;

Cache::Cache(const int tamaño_cache, string nombre_cache)
    : tamaño(tamaño_cache), nombre(std::move(nombre_cache)) {
    entradas.resize(tamaño);
}

bool Cache::buscar(const Direccion direccion, Numero& dato) {
    for (int i = 0; i < tamaño; ++i) {
        if (entradas[i].valido && entradas[i].direccion == direccion) {
            dato = entradas[i].dato;
            actualizar_lru(i);

            ++hits;
            return true;
        }
    }

    ++misses;
    return false;
}

void Cache::escribir(const Direccion direccion, const Numero dato) {
    for (int i = 0; i < tamaño; ++i) {
        if (entradas[i].valido && entradas[i].direccion == direccion) {
            entradas[i].dato = dato;
            actualizar_lru(i);

            return;
        }
    }

    for (int i = 0; i < tamaño; ++i) {
        if (!entradas[i].valido) {
            entradas[i].direccion = direccion;
            entradas[i].dato = dato;
            entradas[i].valido = true;

            actualizar_lru(i);
            return;
        }
    }

    const int lru_indice = encontrar_lru();

    entradas[lru_indice].direccion = direccion;
    entradas[lru_indice].dato = dato;
    entradas[lru_indice].valido = true;

    actualizar_lru(lru_indice);
}

void Cache::invalidar() {
    for (auto& entrada : entradas) entrada.valido = false;

    hits = 0;
    misses = 0;
    contador_acceso = 0;
}

int Cache::calcular_hits() const {
    return hits;
}

int Cache::calcular_misses() const {
    return misses;
}

int Cache::encontrar_lru() const {
    int lru_indice = 0;
    int menor_acceso = entradas[0].ultimo_acceso;

    for (int i = 1; i < tamaño; ++i) {
        if (entradas[i].ultimo_acceso < menor_acceso) {
            menor_acceso = entradas[i].ultimo_acceso;
            lru_indice = i;
        }
    }

    return lru_indice;
}

void Cache::actualizar_lru(const int indice) {
    entradas[indice].ultimo_acceso = ++contador_acceso;
}
