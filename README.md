# 🖥️ Simulador de Arquitectura x86

Un simulador interactivo de arquitectura x86 desarrollado en C++ con jerarquía de cache multinivel y API completa para integración con Excel.

## 🎯 Objetivo

Este proyecto es una herramienta educativa que permite visualizar y comprender el funcionamiento de los principales componentes de una computadora basada en arquitectura x86, incluyendo CPU, memoria principal y sistema de caches L1/L2/L3.

## 🏗️ Arquitectura del Proyecto

### Componentes Principales

- **CPU** (`cpu.hpp/cpp`): Procesador con 8 registros de 32 bits (EAX-EDI) y banderas
- **ALU** (`alu.hpp/cpp`): Unidad aritmético-lógica para operaciones
- **Memoria** (`memoria.hpp/cpp`): Memoria principal de 1024 bytes
- **JerarquiaCache** (`jerarquia_cache.hpp/cpp`): Sistema de 3 niveles de cache
- **Parser** (`parser.hpp/cpp`): Intérprete de assembly simplificado
- **MotorSimulacion** (`motor_simulacion.hpp/cpp`): Controlador principal
- **SalidaJson** (`salida_json.hpp/cpp`): Serialización JSON modular

### Instrucciones Soportadas

- `MOV` - Movimiento de datos entre registros o valores inmediatos
- `ADD` - Suma aritmética
- `SUB` - Resta aritmética  
- `LOAD` - Carga desde memoria a registro
- `STORE` - Almacena registro en memoria
- `JMP` - Salto incondicional
- `NOP` - No operación

## 🚀 Compilación

### Requisitos
- CMake 3.10+
- Compilador C++20 compatible
- Windows (para DLL) o Linux/MacOS (para ejecutable)

### Compilar el Proyecto

```bash
mkdir build
cd build
cmake ..
make
```

### Compilar DLL para Excel (Windows)

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake -G "MinGW Makefiles" ..
mingw32-make
```

Esto genera:
- `CODE.exe` - Ejecutable standalone
- `CODE.dll` - Biblioteca para Excel/VBA

## 📊 API de la DLL para Excel

### Funciones de Control

| Función | Descripción |
|---------|-------------|
| `inicializar_simulador()` | Inicializa nueva instancia |
| `cargar_programa(archivo)` | Carga programa assembly |
| `ejecutar_paso()` | Ejecuta una instrucción |
| `reiniciar()` | Reinicia al estado inicial |
| `finalizar_simulador()` | Libera memoria |

### Funciones de Serialización JSON

| Función | Retorna |
|---------|---------|
| `obtener_registros_buffer()` | Solo registros CPU |
| `obtener_memoria_buffer()` | Solo contenido memoria |
| `obtener_caches_buffer()` | Solo estadísticas cache |
| `obtener_estado_buffer()` | Estado sin caches |
| `obtener_estado_con_caches_buffer()` | Estado completo |

## 📝 Ejemplo de Uso

### Programa Assembly
```assembly
MOV EAX, 100
STORE EAX, 0
MOV EBX, 200
ADD EAX, EBX
STORE EAX, 4
```

### Uso desde C++
```cpp
MotorSimulacion motor;
motor.cargar_programa("programa.asm");

while (motor.esta_ejecutando()) {
    motor.siguiente_paso();
    cout << motor.obtener_estado_con_caches() << endl;
}
```

### Uso desde Excel/VBA
```vba
Private Declare PtrSafe Function inicializar_simulador Lib "CODE.dll" () As Long
Private Declare PtrSafe Sub obtener_estado_con_caches_buffer Lib "CODE.dll" (ByVal buffer As String, ByVal tamaño As Long)

Sub SimularPrograma()
    inicializar_simulador
    cargar_programa "programa.asm"
    
    Dim buffer As String * 5000
    obtener_estado_con_caches_buffer buffer, 5000
    Range("A1").Value = Trim(buffer)
End Sub
```

## 🗂️ Estructura de Archivos

```
CODE/
├── src/
│   ├── alu.cpp/hpp              # Unidad aritmético-lógica
│   ├── cache.cpp/hpp            # Cache individual
│   ├── jerarquia_cache.cpp/hpp  # Sistema de caches L1/L2/L3
│   ├── cpu.cpp/hpp              # Procesador x86
│   ├── memoria.cpp/hpp          # Memoria principal
│   ├── motor_simulacion.cpp/hpp # Motor principal
│   ├── parser.cpp/hpp           # Parser assembly
│   └── salida_json.cpp          # Serialización JSON
├── include/
│   ├── tipos.hpp                # Definiciones de tipos
│   └── salida_json.hpp          # Headers JSON
├── main.cpp                     # Punto de entrada y API DLL
└── CMakeLists.txt              # Configuración build
```
