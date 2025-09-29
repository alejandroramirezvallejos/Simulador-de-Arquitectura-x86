#pragma once
#include "../include/tipos.hpp"

class CPU {
    public:
        Numero registros[8]{};
        Numero contador{};
        bool banderas[3]{};

        CPU() = default;

        [[nodiscard]] Numero obtener_registro(Registro registro) const noexcept;
        void establecer_registro(Registro registro, Numero numero) noexcept;
        [[nodiscard]] Numero obtener_contador() const noexcept;
        void establecer_contador(Numero numero) noexcept;
        [[nodiscard]] bool obtener_bandera(Bandera bandera) const noexcept;
        void establecer_bandera(Bandera bandera, bool valor) noexcept;
};
