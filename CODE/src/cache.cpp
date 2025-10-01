#include "cache.hpp"
#include "memoria.hpp"
#include <sstream>
#include <algorithm>

Cache::Cache(const int tamaño, string nombre) : tamaño(tamaño), nombre(std::move(nombre)) {
    entradas.resize(tamaño);
}

bool Cache::buscar(const Direccion direccion, Numero& dato) const {
    for (int i = 0; i < tamaño; ++i) {
        if (entradas[i].valido && entradas[i].direccion == direccion) {
            dato = entradas[i].dato;
            actualizar_lru(i);
            ++aciertos;

            return true;
        }
    }

    ++fallos;

    return false;
}

void Cache::escribir(const Direccion direccion, const Numero dato) const {
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

    const int indice = encontrar_lru();
    entradas[indice].direccion = direccion;
    entradas[indice].dato = dato;
    entradas[indice].valido = true;
    actualizar_lru(indice);
}

void Cache::invalidar() const {
    for (auto& entrada : entradas) entrada.valido = false;

    aciertos = fallos = contador_acceso = 0;
}

int Cache::calcular_aciertos() const {
    return aciertos;
}
int Cache::calcular_fallos() const {
    return fallos;
}

int Cache::encontrar_lru() const {
    int indice = 0;
    int ultimo_acceso = entradas[0].ultimo_acceso;

    for (int i = 1; i < tamaño; ++i) {
        if (entradas[i].ultimo_acceso < ultimo_acceso) {
            ultimo_acceso = entradas[i].ultimo_acceso;
            indice = i;
        }
    }

    return indice;
}

void Cache::actualizar_lru(const int indice) const {
    entradas[indice].ultimo_acceso = ++contador_acceso;
}
