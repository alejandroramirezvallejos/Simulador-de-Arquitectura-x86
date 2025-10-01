#pragma once
#include "../include/tipos.hpp"

class CPU {
    public:
        Numero registros[17]{};
        Numero registros_internos[8]{};
        Numero contador{};
        bool banderas[3]{};
        Numero pila[1024]{};
        int puntero{1024};

        CPU();

        [[nodiscard]] Numero obtener_registro(Registro registro) const noexcept;
        void establecer_registro(Registro registro, Numero numero) noexcept;
        [[nodiscard]] Numero obtener_registro_interno(RegistroInterno registro) const noexcept;
        void establecer_registro_interno(RegistroInterno registro, Numero numero) noexcept;
        [[nodiscard]] Numero obtener_contador() const noexcept;
        void establecer_contador(Numero numero) noexcept;
        [[nodiscard]] bool obtener_bandera(Bandera bandera) const noexcept;
        void establecer_bandera(Bandera bandera, bool valor) noexcept;
        [[nodiscard]] bool pila_vacia() const noexcept;
        [[nodiscard]] bool pila_llena() const noexcept;
        [[nodiscard]] std::string obtener_estado_registros_internos() const;
        void push(Numero numero);
        Numero pop();
};
