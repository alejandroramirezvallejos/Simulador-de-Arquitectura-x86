# Simulador de Arquitectura x86

## Descripción
Simulador de arquitectura x86 que procesa instrucciones en ensamblador AT&T y ejecuta operaciones básicas de CPU incluyendo manejo de registros, memoria, pila y cache.

## Correcciones Implementadas

### 1. Parser Mejorado
- **Direcciones de memoria con offset**: Ahora maneja correctamente direcciones como `-4(%rbp)`, `8(%rsp)`
- **Registros 32-bit**: Soporte completo para registros EAX, EBX, ECX, EDX, etc.
- **Valores inmediatos**: Procesamiento correcto de valores con prefijo `$`
- **Sintaxis AT&T**: Compatible con sintaxis GNU Assembler

### 2. Motor de Simulación Corregido
- **Carga de programas**: Establece correctamente el estado de ejecución
- **Instrucciones MOVL**: Manejo correcto de direcciones de memoria con offset relativo
- **Instrucciones ADDL**: Soporte para operaciones con memoria
- **Gestión de la pila**: PUSHQ y POPQ funcionando correctamente

### 3. Funciones DLL para VBA Excel
- `inicializar()`: Crear instancia del simulador
- `cargar(archivo)`: Cargar programa ASM
- `ejecutar_paso()`: Ejecutar siguiente instrucción
- `obtener_estado()`: Estado básico de CPU y registros
- `obtener_estado_cache()`: Estado con información de cache L1/L2/L3
- `obtener_memoria()`: Volcado JSON de memoria RAM
- `esta_ejecutando()`: Verificar si hay programa activo
- `reiniciar()`: Reset completo del simulador
- `limpiar()`: Liberar memoria

### 4. Mejoras de Rendimiento
- Gestión eficiente de memoria
- Debug detallado con historial JSON
- Soporte para múltiples niveles de cache
- Manejo de banderas (CERO, ACARREO, SIGNO)

## Instrucciones Soportadas
- **MOVQ/MOVL**: Movimiento de datos entre registros y memoria
- **ADDQ/ADDL**: Suma de valores inmediatos o registros  
- **SUBQ/SUBL**: Resta de valores inmediatos o registros
- **PUSHQ**: Push a la pila
- **POPQ**: Pop de la pila
- **JMP**: Saltos incondicionales

## Ejemplo de Programa ASM
```asm
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
movl $1, -4(%rbp)
movl -4(%rbp), %eax
addl $1, %eax
movl %eax, -8(%rbp)
movl $0, %eax
```

## Compilación
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Uso desde VBA Excel
```vb
Declare Function inicializar Lib "simulador.dll" () As Integer
Declare Function cargar Lib "simulador.dll" (ByVal archivo As String) As Integer
Declare Function ejecutar_paso Lib "simulador.dll" () As Integer
```

## Arquitectura del Simulador
- **CPU**: 17 registros de 64-bit, banderas, contador de programa
- **Memoria**: 1024 bytes de RAM simulada
- **Cache**: Jerarquía L1/L2/L3 con estadísticas de hit/miss
- **Debugger**: Historial completo de ejecución en JSON
- **Parser**: Análisis sintáctico de ensamblador AT&T

Las correcciones implementadas solucionan los problemas de carga de programas, procesamiento de instrucciones con direcciones de memoria y compatibilidad con Excel VBA.
