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
        mutable vector<EntradaCache> entradas;
        int tamaño;
        string nombre;

        Cache(int tamaño, string nombre);

        bool buscar(Direccion direccion, Numero& dato) const;
        void escribir(Direccion direccion, Numero dato) const;
        void invalidar() const;
        [[nodiscard]] int calcular_aciertos() const;
        [[nodiscard]] int calcular_fallos() const;

    private:
        mutable int aciertos{};
        mutable int fallos{};
        mutable int contador_acceso{};

        [[nodiscard]] int encontrar_lru() const;
        void actualizar_lru(int indice) const;
};
