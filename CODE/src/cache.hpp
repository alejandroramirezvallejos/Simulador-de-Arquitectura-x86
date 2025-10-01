#pragma once
#include "../include/tipos.hpp"
#include <vector>
#include <unordered_map>
#include <string>
using std::vector;
using std::unordered_map;
using std::string;

struct EntradaCache {
    Direccion direccion{};
    Numero dato{};
    bool valido{false};
    int ultimo_acceso{};
};

class Cache {
    public:
        vector<EntradaCache> entradas;
        int tamaño;
        int contador_acceso{};
        string nombre;

        Cache(int tamaño_cache, string nombre_cache);

        bool buscar(Direccion direccion, Numero& dato);
        void escribir(Direccion direccion, Numero dato);
        void invalidar();
        [[nodiscard]] int calcular_hits() const;
        [[nodiscard]] int calcular_misses() const;

    private:
        int hits{};
        int misses{};

        [[nodiscard]] int encontrar_lru() const;
        void actualizar_lru(int indice);
};
