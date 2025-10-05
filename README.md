# Simulador de Arquitectura x86

## Descripción General

Este proyecto presenta un simulador interactivo de arquitectura x86 diseñado con fines educativos. La herramienta permite visualizar y comprender el funcionamiento interno de los principales componentes de un procesador moderno, facilitando el aprendizaje práctico de conceptos fundamentales de arquitectura de computadoras.

El simulador está implementado en Excel con macros VBA y soporta código ensamblador en sintaxis AT&T, proporcionando una representación visual del flujo de datos y control a través de un pipeline de cinco etapas.

---

## Tabla de Contenidos

1. [Características Principales](#características-principales)
2. [Fundamentos Teóricos](#fundamentos-teóricos)
   - [2.1 Unidad de Control](#21-unidad-de-control-control-unit)
   - [2.2 Unidad Aritmético-Lógica (ALU)](#22-unidad-aritmético-lógica-alu)
   - [2.3 Banco de Registros](#23-banco-de-registros-registers)
   - [2.4 Unidad de Memoria](#24-unidad-de-memoria-memory-unit)
   - [2.5 Memoria Virtual](#25-memoria-virtual)
   - [2.6 Memoria Caché](#26-memoria-caché)
   - [2.7 Arquitecturas: Von Neumann vs. Harvard](#27-arquitecturas-von-neumann-vs-harvard)
   - [2.8 Ciclo de Instrucción](#28-ciclo-de-instrucción)
   - [2.9 Pipeline de Instrucciones](#29-pipeline-de-instrucciones)
3. [Arquitectura del Simulador](#arquitectura-del-simulador)
4. [Componentes Implementados](#componentes-implementados)
5. [Manejo de Hazards y Dependencias](#manejo-de-hazards-y-dependencias)
6. [Ejemplos de Uso](#ejemplos-de-uso)
7. [Instalación y Configuración](#instalación-y-configuración)
8. [Referencias](#referencias)

---

## Características Principales

- **Visualización interactiva** del flujo de datos a través del pipeline
- **Soporte para ensamblador x86** en sintaxis AT&T
- **Pipeline de 5 etapas** (IF, ID, EX, MEM, WB)
- **Sistema de memoria jerárquico** con cachés L1 (I-Cache y D-Cache), L2 y L3
- **Detección automática de hazards** (RAW, WAW, WAR)
- **Implementación de forwarding** para optimización del pipeline
- **Gestión dinámica de registros** de propósito general (RAX-R15)
- **Simulación de memoria virtual** con tabla de páginas conceptual
- **Representación visual de flags** (ZF, SF, CF, OF)

---

## Fundamentos Teóricos

### 2.1 Unidad de Control (Control Unit)

#### Conceptualización

La Unidad de Control (UC) es el componente responsable de coordinar y dirigir las operaciones del procesador. Actúa como el "director de orquesta" del sistema, interpretando instrucciones y generando señales de control para activar los componentes apropiados en el momento correcto.

#### Diseño en el Simulador

En nuestra implementación, la UC gestiona:

- **Program Counter (PC)**: Mantiene la dirección de la próxima instrucción a ejecutar
- **Instruction Register (IR)**: Almacena la instrucción actualmente en decodificación
- **Memory Address Register (MAR)**: Contiene la dirección de memoria a acceder
- **Memory Data Register (MDR)**: Almacena temporalmente datos leídos o a escribir en memoria

**Funciones implementadas:**

```vba
Sub Fetch()
    ' Obtiene la instrucción apuntada por PC
    ' Actualiza IR con la instrucción recuperada
    ' Consulta I-Cache antes de acceder a memoria principal
End Sub

Sub Decode()
    ' Decodifica la instrucción en IR
    ' Identifica opcode y operandos
    ' Prepara señales de control para la etapa de ejecución
End Sub
```

La UC implementa el ciclo fetch-decode-execute, coordinando el acceso a memoria, la decodificación de instrucciones y la activación de la ALU.

---

### 2.2 Unidad Aritmético-Lógica (ALU)

#### Conceptualización

La ALU es el componente que realiza operaciones aritméticas (suma, resta, multiplicación, división) y lógicas (AND, OR, XOR, NOT) sobre los datos. Es el "cerebro computacional" del procesador.

#### Diseño en el Simulador

Nuestra ALU incluye:

- **Entradas duales**: Dos buses de entrada (Input1, Input2) para operandos
- **Selector de operación**: Determina qué operación ejecutar
- **Salida de resultado**: Bus de salida conectado al sistema de writeback
- **Registro de flags**: Actualiza automáticamente ZF, SF, CF, OF según el resultado

**Operaciones soportadas:**

| Operación  | Descripción                     | Actualiza Flags |
| ---------- | ------------------------------- | --------------- |
| ADD/SUB    | Aritmética entera               | Sí              |
| MUL/DIV    | Multiplicación/División         | Sí              |
| AND/OR/XOR | Operaciones lógicas             | Sí              |
| CMP        | Comparación (SUB sin escritura) | Sí              |
| MOV        | Transferencia de datos          | No              |

**Implementación:**

```vba
Sub EjecutarEnALU(Operacion As String)
    ' 1. Parsear instrucción y extraer operandos
    ' 2. Obtener valores de registros/memoria/inmediatos
    ' 3. Ejecutar operación seleccionada
    ' 4. Actualizar flags (ZF, SF, CF, OF)
    ' 5. Colocar resultado en registro temporal (Z1/Z2)
End Sub
```

---

### 2.3 Banco de Registros (Registers)

#### Conceptualización

Los registros son elementos de almacenamiento ultrarrápidos dentro del procesador. En arquitectura x86-64, existen 16 registros de propósito general de 64 bits, más registros especiales como el puntero de instrucción (RIP) y el puntero de pila (RSP).

#### Diseño en el Simulador

**Jerarquía de registros implementada:**

```
64-bit: RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP, R8-R15
32-bit: EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP, R8D-R15D
16-bit: AX, BX, CX, DX, SI, DI, BP, SP, R8W-R15W
8-bit:  AL, BL, CL, DL, SIL, DIL, BPL, SPL, R8B-R15B
```

**Características del sistema de registros:**

- **Normalización automática**: Todos los nombres de registro se normalizan internamente a su versión de 64 bits
- **Detección dinámica**: El sistema escanea el código ensamblador para identificar qué registros se utilizan
- **Renderización visual**: Los registros se muestran en una tabla con nombre, valor hexadecimal y decimal
- **Resaltado dinámico**: Los registros se colorean al ser leídos o escritos para facilitar el seguimiento

**Funciones principales:**

```vba
Function LeerRegistro(nombreReg As String) As Long
    ' Normaliza el nombre del registro
    ' Retorna el valor almacenado
    ' Si no existe, lo crea dinámicamente
End Function

Sub EscribirRegistro(nombreReg As String, valor As Long)
    ' Normaliza el nombre del registro
    ' Actualiza el valor en el diccionario interno
    ' Refresca la visualización en Excel
End Sub
```

---

### 2.4 Unidad de Memoria (Memory Unit)

#### Conceptualización

La Unidad de Memoria es el subsistema responsable del almacenamiento de instrucciones y datos. Coordina el acceso a la jerarquía de memoria, desde los registros hasta el almacenamiento secundario, pasando por cachés y RAM.

#### Diseño en el Simulador

**Estructura implementada:**

1. **Memoria Principal (RAM simulada)**:

   - Implementada mediante un `Scripting.Dictionary` global
   - Claves formato: `"MEM_<dirección>"`
   - Valores: datos de 32/64 bits

2. **Interfaz de acceso**:

   ```vba
   Function LeerMemoria(expresion As String) As Long
       ' Parsea expresiones como "-4(%rbp)" o "(%rax)"
       ' Calcula dirección real: base + offset
       ' Consulta D-Cache antes de RAM
       ' Retorna el valor almacenado
   End Function

   Sub EscribirMemoria(expresion As String, valor As Long)
       ' Calcula dirección efectiva
       ' Actualiza memoria global
       ' Invalida/actualiza entrada en D-Cache
   End Sub
   ```

3. **Visualización**:
   - Tabla ordenada por dirección de memoria
   - Formato hexadecimal y decimal
   - Diferenciación de segmentos (stack, heap, código)

---

### 2.5 Memoria Virtual

#### Conceptualización

La memoria virtual es una técnica que proporciona a cada proceso un espacio de direcciones lógico independiente, mapeado a memoria física mediante una tabla de páginas. Esto permite:

- **Aislamiento entre procesos**
- **Uso eficiente de memoria física limitada**
- **Protección de memoria**
- **Soporte para paginación bajo demanda**

#### Diseño en el Simulador

**Modelo conceptual implementado:**

```
Dirección Virtual → MMU → Tabla de Páginas → Dirección Física
      |                                              |
      └──────────────────────────────────────────────┘
                    (Traducción)
```

**Componentes:**

1. **Memory Management Unit (MMU)** (simulada):

   - Intercepta accesos a memoria
   - Traduce direcciones virtuales a físicas
   - Maneja page faults (conceptualmente)

2. **Tabla de Páginas** (simplificada):

   - En la implementación actual, se usa mapeo directo
   - Cada entrada contiene: número de página virtual → marco físico

3. **Visualización**:
   - Rango `RANGO_MEMORIA_VIRTUAL` muestra el espacio de direcciones virtuales
   - Rango `RANGO_MEMORIA_PRINCIPAL` muestra memoria física (RAM)

**Simulación de traducción:**

```vba
' Pseudocódigo conceptual
Function TraducirDireccion(dirVirtual As Long) As Long
    numeroPagina = dirVirtual \ TAMANO_PAGINA
    offset = dirVirtual Mod TAMANO_PAGINA
    marcoFisico = TablaPaginas(numeroPagina)
    dirFisica = marcoFisico * TAMANO_PAGINA + offset
    Return dirFisica
End Function
```

---

### 2.6 Memoria Caché

#### Conceptualización

La memoria caché es una memoria pequeña y ultrarrápida que almacena copias de datos frecuentemente accedidos, reduciendo el tiempo promedio de acceso a memoria. Se organiza en niveles (L1, L2, L3) con compromiso entre tamaño y velocidad.

#### Diseño en el Simulador

**Jerarquía implementada:**

```
CPU
 ├─ L1 I-Cache (Instrucciones) - Más rápida, más pequeña
 ├─ L1 D-Cache (Datos)
 ├─ L2 Cache (Unificada)
 ├─ L3 Cache (Compartida)
 └─ RAM Principal
```

**Características:**

1. **I-Cache (Instruction Cache)**:

   - Almacena instrucciones recientemente ejecutadas
   - Consultada durante la etapa Fetch
   - Formato: `Addr:<PC> | <instrucción>`

2. **D-Cache (Data Cache)**:

   - Almacena datos recientemente accedidos
   - Consultada durante la etapa Memory Access
   - Formato: `Addr:<dirección> | dirección=valor`

3. **Política de reemplazo**:
   - LRU (Least Recently Used) simplificado
   - Al llenarse, se desplazan entradas antiguas

**Implementación:**

```vba
Function BuscarEnCache(cache As Range, direccion As String, _
                       ByRef dato As String) As Boolean
    ' Recorre las celdas del rango de caché
    ' Busca coincidencia con "Addr:<direccion>"
    ' Si encuentra, extrae dato y retorna True (HIT)
    ' Si no encuentra, retorna False (MISS)
End Function

Sub CargarEnCache(cache As Range, dato As String)
    ' Si hay espacio, añade en primera celda vacía
    ' Si está lleno, desplaza entradas (LRU)
    ' Coloca nueva entrada al final
    ' Actualiza visualización y estado de caché
End Sub
```

**Métricas visualizadas:**

- Hit Rate: `(Hits / Total Accesos) × 100%`
- Miss Penalty: Ciclos adicionales en caso de miss
- Estado actual: HIT/MISS con código de colores

---

### 2.7 Arquitecturas: Von Neumann vs. Harvard

#### Arquitectura Von Neumann

**Características:**

- **Memoria unificada**: Instrucciones y datos comparten el mismo espacio de memoria
- **Bus único**: Un solo bus para transferir tanto instrucciones como datos
- **Cuello de botella**: El bus compartido limita el ancho de banda (Von Neumann bottleneck)

**Ventajas:**

- Simplicidad de diseño
- Flexibilidad en el uso de memoria
- Facilita la ejecución de código automodificable

**Desventajas:**

- No se puede acceder simultáneamente a instrucciones y datos
- Menor rendimiento potencial

#### Arquitectura Harvard

**Características:**

- **Memorias separadas**: Espacios físicamente distintos para instrucciones y datos
- **Buses independientes**: Bus de instrucciones y bus de datos separados
- **Paralelismo**: Permite acceso simultáneo a instrucciones y datos

**Ventajas:**

- Mayor ancho de banda total
- Mejor rendimiento en pipelines
- Protección natural contra código malicioso

**Desventajas:**

- Mayor complejidad de hardware
- Uso menos flexible de memoria

#### Implementación en el Simulador

Nuestro simulador adopta una **arquitectura Harvard modificada**:

```
                    CPU
                     |
         ┌───────────┴───────────┐
         |                       |
    I-Cache                  D-Cache
         |                       |
    ┌────┴────┐            ┌────┴────┐
    |         |            |         |
I-Buffer  Decode       ALU/Regs   MEM
         Buffer
```

**Características de nuestra implementación:**

1. **Separación lógica**:

   - I-Cache dedicada para instrucciones (consultada en Fetch)
   - D-Cache dedicada para datos (consultada en Memory Access)
   - Buffers independientes (Fetch Buffer, Decode Buffer)

2. **Memoria principal unificada**:

   - A nivel de RAM, se usa un diccionario único (`memoriaStackGlobal`)
   - Esto facilita la implementación y debugging
   - Refleja la realidad de procesadores modernos (Harvard modificada)

3. **Ventajas obtenidas**:
   - Permite fetch de instrucción y acceso a datos en el mismo ciclo
   - Reduce riesgos estructurales en el pipeline
   - Optimiza el rendimiento del simulador

---

### 2.8 Ciclo de Instrucción

#### Conceptualización

El ciclo de instrucción es el proceso completo que realiza un procesador para ejecutar una única instrucción. En su forma básica consta de tres fases:

1. **Fetch (Búsqueda)**: Obtener la instrucción de memoria
2. **Decode (Decodificación)**: Interpretar la instrucción
3. **Execute (Ejecución)**: Realizar la operación especificada

En procesadores modernos, se añaden fases adicionales:

4. **Memory Access**: Acceder a memoria para loads/stores
5. **Write Back**: Escribir resultados en registros

#### Diseño en el Simulador

**Ciclo detallado implementado:**

```
┌─────────────────────────────────────────────────────────┐
│                   CICLO DE INSTRUCCIÓN                   │
└─────────────────────────────────────────────────────────┘
     │
     ├─► 1. FETCH (IF)
     │    ├─ Leer PC
     │    ├─ Buscar en I-Cache
     │    │   ├─ HIT → Obtener instrucción
     │    │   └─ MISS → Acceder RAM, cargar en caché
     │    ├─ Cargar instrucción en IR
     │    ├─ Actualizar Fetch Buffer
     │    └─ Incrementar PC
     │
     ├─► 2. DECODE (ID)
     │    ├─ Parsear instrucción en IR
     │    ├─ Identificar opcode
     │    ├─ Extraer operandos (destino, fuente1, fuente2)
     │    ├─ Cargar en Decode Buffer
     │    ├─ Detectar dependencias (hazards)
     │    └─ Generar señales de control
     │
     ├─► 3. EXECUTE (EX)
     │    ├─ Leer operandos de registros/memoria/inmediatos
     │    ├─ Enviar operandos a ALU
     │    ├─ Ejecutar operación según opcode
     │    ├─ Calcular direcciones efectivas (loads/stores)
     │    ├─ Actualizar flags (ZF, SF, CF, OF)
     │    └─ Colocar resultado en registro temporal (Z1/Z2)
     │
     ├─► 4. MEMORY ACCESS (MEM)
     │    ├─ Si es LOAD:
     │    │   ├─ Buscar en D-Cache
     │    │   ├─ HIT → Obtener dato
     │    │   └─ MISS → Acceder RAM, cargar en caché
     │    ├─ Si es STORE:
     │    │   ├─ Escribir en D-Cache
     │    │   └─ Actualizar RAM (write-through/write-back)
     │    └─ Si es otra instrucción: pasar resultado
     │
     └─► 5. WRITE BACK (WB)
          ├─ Escribir resultado en registro destino
          ├─ Actualizar visualización de registros
          ├─ Limpiar buffers temporales (Z1/Z2)
          └─ Marcar instrucción como completada
```

**Implementación en VBA:**

```vba
Sub AvanzarCiclo()
    Call Fetch()           ' Etapa 1: IF
    Call Decode()          ' Etapa 2: ID
    Call Execute()         ' Etapa 3: EX
    Call MemoryAccess()    ' Etapa 4: MEM
    Call WriteBack()       ' Etapa 5: WB
End Sub
```

**Timing y visualización:**

- Cada etapa se resalta visualmente con colores específicos
- Pausas configurables (`Application.Wait`) entre etapas
- Actualización en tiempo real de shapes y celdas
- Indicadores de estado por etapa (COLOR_ACTIVO, etc.)

---

### 2.9 Pipeline de Instrucciones

#### Conceptualización

El pipeline es una técnica de implementación que permite superponer la ejecución de múltiples instrucciones. Mientras una instrucción está en fase de ejecución, otra puede estar decodificándose y una tercera puede estar siendo recuperada de memoria.

**Analogía:** Como una línea de ensamblaje en una fábrica, donde diferentes productos (instrucciones) están en diferentes etapas de fabricación simultáneamente.

#### Beneficios del Pipeline

1. **Mayor throughput**: Se completa una instrucción por ciclo (en ideal)
2. **Mejor utilización de recursos**: Cada unidad funcional trabaja constantemente
3. **Menor CPI (Cycles Per Instruction)**: Idealmente CPI = 1

**Speedup teórico:**

```
Speedup = (Número de etapas) / (1 + Fracción de hazards)
```

Para nuestro pipeline de 5 etapas sin hazards: **Speedup ≈ 5×**

#### Diseño en el Simulador

**Pipeline de 5 etapas:**

```
┌────┐   ┌────┐   ┌────┐   ┌─────┐   ┌────┐
│ IF │──▶│ ID │──▶│ EX │──▶│ MEM │──▶│ WB │
└────┘   └────┘   └────┘   └─────┘   └────┘
  T1       T2       T3       T4        T5
```

**Ejemplo de ejecución pipeline:**

```
Ciclo │ Instr1 │ Instr2 │ Instr3 │ Instr4 │ Instr5
──────┼────────┼────────┼────────┼────────┼────────
  1   │   IF   │        │        │        │
  2   │   ID   │   IF   │        │        │
  3   │   EX   │   ID   │   IF   │        │
  4   │  MEM   │   EX   │   ID   │   IF   │
  5   │   WB   │  MEM   │   EX   │   ID   │   IF
  6   │        │   WB   │  MEM   │   EX   │   ID
  7   │        │        │   WB   │  MEM   │   EX
  8   │        │        │        │   WB   │  MEM
  9   │        │        │        │        │   WB
```

**Estructura de datos:**

```vba
Type InstruccionPipeline
    instruccion As String
    etapa As String  ' "IF", "ID", "EX", "MEM", "WB"
    RegistroDestino As String
    registrosFuente As String
    ciclo As Long
End Type

Dim pipeline(1 To 5) As InstruccionPipeline
```

**Algoritmo de simulación:**

```vba
Sub SimularPipelineCPU(rangoInstrucciones As Range, rangoPipeline As Range)
    Dim ciclo As Long: ciclo = 0
    Dim pc As Long: pc = 1
    Dim totalInstrucciones As Long

    Do While (pc <= totalInstrucciones) Or HayInstruccionesEnPipeline(pipeline)
        ciclo = ciclo + 1

        ' Procesar etapas en orden inverso para evitar sobrescritura
        If Not IsEmpty(pipeline(5).instruccion) Then
            ' WB: Escribir resultado
            Call EscribirEnTablaPipeline(rangoPipeline, pipeline(5), "WB")
        End If

        If Not IsEmpty(pipeline(4).instruccion) Then
            ' MEM: Acceso a memoria
            Call EscribirEnTablaPipeline(rangoPipeline, pipeline(4), "MEM")
            pipeline(5) = pipeline(4)
        End If

        If Not IsEmpty(pipeline(3).instruccion) Then
            ' EX: Ejecución en ALU
            Call EscribirEnTablaPipeline(rangoPipeline, pipeline(3), "EX")
            pipeline(4) = pipeline(3)
        End If

        If Not IsEmpty(pipeline(2).instruccion) Then
            ' ID: Decodificación y detección de hazards
            Dim hayHazard As Boolean
            hayHazard = DetectarHazard(pipeline(2), pipeline(3), pipeline(4))

            If hayHazard Then
                ' Insertar STALL y BUBBLE
                Call InsertarStall(rangoPipeline, ciclo)
                ' No avanzar IF este ciclo
            Else
                Call EscribirEnTablaPipeline(rangoPipeline, pipeline(2), "ID")
                pipeline(3) = pipeline(2)
            End If
        End If

        If pc <= totalInstrucciones And Not hayHazard Then
            ' IF: Fetch nueva instrucción
            pipeline(1).instruccion = rangoInstrucciones.Cells(pc, 1).Value
            pipeline(1).etapa = "IF"
            pipeline(1).ciclo = ciclo
            Call ExtraerRegistros(pipeline(1).instruccion, _
                                  pipeline(1).RegistroDestino, _
                                  pipeline(1).registrosFuente)
            Call EscribirEnTablaPipeline(rangoPipeline, pipeline(1), "IF")
            pipeline(2) = pipeline(1)
            pc = pc + 1
        End If

        Application.Wait Now + TimeValue("00:00:01")
        DoEvents
    Loop
End Sub
```

#### Hazards en el Pipeline

**Tipos de hazards implementados:**

1. **Hazards estructurales**: Conflictos por recursos compartidos (minimizados por arquitectura Harvard)

2. **Hazards de datos** (Data Hazards):

   - **RAW (Read After Write)**: La instrucción lee un registro antes de que la anterior termine de escribirlo
   - **WAW (Write After Write)**: Dos instrucciones escriben el mismo registro
   - **WAR (Write After Read)**: Menos problemático en pipeline in-order

3. **Hazards de control**: Saltos y cambios de flujo (branch prediction no implementado actualmente)

**Ejemplo de RAW Hazard:**

```assembly
movl $10, %eax     # I1: EAX = 10
addl %eax, %ebx    # I2: EBX = EBX + EAX (depende de I1)
```

Sin forwarding:

```
Ciclo │ I1  │ I2
──────┼─────┼──────
  1   │ IF  │
  2   │ ID  │ IF
  3   │ EX  │ ID (detecta hazard!)
  4   │ MEM │ STALL
  5   │ WB  │ STALL
  6   │     │ EX (ahora EAX está disponible)
```

Con forwarding (EX→EX):

```
Ciclo │ I1  │ I2
──────┼─────┼──────
  1   │ IF  │
  2   │ ID  │ IF
  3   │ EX  │ ID
  4   │ MEM │ EX (forwarding desde I1.EX)
  5   │ WB  │ MEM
```

**Detección de hazards:**

```vba
Function DetectarHazard(instrActual As InstruccionPipeline, _
                        instrEX As InstruccionPipeline, _
                        instrMEM As InstruccionPipeline) As Boolean
    Dim hazard As Boolean: hazard = False

    ' Verificar si hay dependencia RAW
    If instrActual.registrosFuente <> "" Then
        ' Comparar con registro destino de instrucciones en EX y MEM
        If InStr(instrActual.registrosFuente, instrEX.RegistroDestino) > 0 Then
            hazard = True
        ElseIf InStr(instrActual.registrosFuente, instrMEM.RegistroDestino) > 0 Then
            hazard = True
        End If
    End If

    DetectarHazard = hazard
End Function
```

**Técnicas de mitigación:**

1. **Stalling (Pipeline Bubbles)**:

   - Detener el pipeline hasta que la dependencia se resuelva
   - Inserta "burbujas" (NOPs) en el pipeline
   - Simple pero penaliza el rendimiento

2. **Forwarding (Bypassing)**:

   - Enviar resultados directamente desde etapas posteriores a anteriores
   - Rutas: EX→EX, MEM→EX, WB→EX
   - Implementación visual con flechas en el diagrama

3. **Reordenamiento de código** (compilador):
   - Insertar instrucciones independientes entre dependientes
   - No implementado en el simulador actual

---

## Arquitectura del Simulador

### Diagrama General

```
┌───────────────────────────────────────────────────────────────────┐
│                        USUARIO (Excel UI)                         │
└───────────────────────────────────────────────────────────────────┘
                                 │
                    ┌────────────┴────────────┐
                    │   Código Ensamblador    │
                    │   (Sintaxis AT&T)       │
                    └────────────┬────────────┘
                                 │
┌────────────────────────────────┴────────────────────────────────┐
│                     CAPA DE CONTROL (VBA)                       │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │  CargarEnsamblador() → InicializarSistemaRegistros()    │  │
│  │  AvanzarCiclo() / SimularPipelineCPU()                  │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
         │                    │                    │
    ┌────┴────┐         ┌─────┴─────┐       ┌─────┴─────┐
    │  UNIDAD │         │  PIPELINE │       │  SISTEMA  │
    │    DE   │         │ (5 ETAPAS)│       │    DE     │
    │ CONTROL │         └─────┬─────┘       │  MEMORIA  │
    └────┬────┘               │             └─────┬─────┘
         │                    │                    │
    ┌────┴────────────────────┴────────────────────┴─────┐
    │              DATAPATH (Ruta de Datos)              │
    │  ┌──────┐  ┌─────┐  ┌──────┐  ┌────────┐  ┌────┐ │
    │  │ PC/  │→ │Fetch│→ │Decode│→ │  ALU   │→ │ WB │ │
    │  │ IR   │  │Buffer│  │Buffer│  │  +     │  │    │ │
    │  │      │  │      │  │      │  │ Regs   │  │    │ │
    │  └──────┘  └─────┘  └──────┘  └────┬───┘  └────┘ │
    │                                     │              │
    │                            ┌────────┴────────┐     │
    │                            │  Memory Access  │     │
    │                            └────────┬────────┘     │
    └─────────────────────────────────────┼──────────────┘
                                          │
    ┌─────────────────────────────────────┴──────────────┐
    │           JERARQUÍA DE MEMORIA                     │
    │  ┌───────────┐  ┌───────────┐  ┌────────────┐    │
    │  │  I-Cache  │  │  D-Cache  │  │  L2 Cache  │    │
    │  └─────┬─────┘  └─────┬─────┘  └──────┬─────┘    │
    │        └────────────┬──────────────────┘          │
    │                ┌────┴────┐                        │
    │                │   L3    │                        │
    │                └────┬────┘                        │
    │                ┌────┴────┐                        │
    │                │   RAM   │                        │
    │                │(memoria │                        │
    │                │StackG.) │                        │
    │                └─────────┘                        │
    └────────────────────────────────────────────────────┘
```

### Flujo de Datos End-to-End

1. **Carga**: Usuario ingresa código → `CargarEnsamblador()` → Normalización → Inicialización de registros y memoria
2. **Fetch**: PC → I-Cache → IR → Fetch Buffer
3. **Decode**: Fetch Buffer → Parser → Decode Buffer → Extracción de registros
4. **Execute**: Decode Buffer → ALU → Operandos (Registros/Memoria/Inmediatos) → Resultado en Z1/Z2
5. **Memory**: Z1/Z2 → D-Cache → RAM (si es load/store)
6. **WriteBack**: Z1/Z2 → Registro destino → Actualización visual

---

## Componentes Implementados

### Listado Completo de Módulos VBA

| Módulo                 | Descripción                          | Funciones Clave                                                            |
| ---------------------- | ------------------------------------ | -------------------------------------------------------------------------- |
| **Módulo1_Pipeline**   | Diagrama visual y creación de shapes | `CrearDiagramaPipeline`, `CrearFlechaForwarding`                           |
| **Módulo2_Simulacion** | Motor del pipeline                   | `SimularPipelineCPU`, `DetectarHazard`                                     |
| **Módulo3_Registros**  | Gestión dinámica de registros        | `LeerRegistro`, `EscribirRegistro`, `InicializarSistemaRegistros`          |
| **Módulo4_ALU**        | Ejecución de instrucciones           | `EjecutarEnALU`, `ActualizarFlags`                                         |
| **Módulo5_Memoria**    | Subsistema de memoria                | `LeerMemoria`, `EscribirMemoria`, `MostrarMemoriaFormatted`                |
| **Módulo6_Cache**      | Gestión de cachés                    | `BuscarEnCache`, `CargarEnCache`, `CargarEnCacheAcumulativo`               |
| **Módulo7_Control**    | Ciclo de instrucción                 | `AvanzarCiclo`, `Fetch`, `Decode`, `Execute`, `MemoryAccess`, `WriteBack`  |
| **Módulo8_Parser**     | Parsing AT&T                         | `ParsearInstruccionDirecta`, `ParsearOperando`, `NormalizarNombreRegistro` |
| **Módulo9_Utilidades** | Funciones auxiliares                 | `ResaltarTemporal`, `LimpiarMemoria`, `CompactarMemoria`                   |

---

## Manejo de Hazards y Dependencias

### Política Sin Forwarding

Cuando se detecta un hazard RAW:

1. La instrucción dependiente se detiene en ID
2. Se insertan burbujas (STALL) en la tabla visual
3. El pipeline se congela hasta que la instrucción productora complete WB
4. Penalización: 2-3 ciclos por dependencia

### Política Con Forwarding

Implementación de rutas de bypass:

- **EX → EX**: Forwarding desde ALU de instrucción anterior
- **MEM → EX**: Forwarding desde etapa de memoria
- **WB → EX**: Forwarding desde writeback (raro, pero posible)

Reducción de stalls:

- Dependencias ALU-ALU: 0 ciclos de penalización
- Load-use: 1 ciclo de penalización (inevitable)

### Visualización

- **Flechas rojas**: Indican forwarding activo
- **Celdas amarillas**: STALL insertado
- **Celdas grises**: Burbuja (BUBBLE/NOP)

---

## Ejemplos de Uso

### Ejemplo 1: Programa Simple

```assembly
pushq %rbp
movq %rsp, %rbp
movl $9, -4(%rbp)
movl $11, -8(%rbp)
movl -4(%rbp), %edx
movl -8(%rbp), %eax
addl %edx, %eax
movl %eax, -12(%rbp)
movl $0, %eax
leave
ret
```

**Análisis:**

- **Línea 3**: Store inmediato 9 en `[RBP-4]`
- **Línea 4**: Store inmediato 11 en `[RBP-8]`
- **Línea 5**: Load `[RBP-4]` → EDX (hazard potencial con línea 3)
- **Línea 6**: Load `[RBP-8]` → EAX (hazard potencial con línea 4)
- **Línea 7**: ADD EDX + EAX → EAX (hazard RAW con líneas 5 y 6)

### Ejemplo 2: Tabla Ciclo-a-Ciclo

Para las instrucciones del Ejemplo 1 (líneas 5-7):

**Sin Forwarding:**

| Ciclo | movl -4(%rbp), %edx | movl -8(%rbp), %eax | addl %edx, %eax |
| ----- | ------------------- | ------------------- | --------------- |
| 1     | IF                  |                     |                 |
| 2     | ID                  | IF                  |                 |
| 3     | EX                  | ID                  | IF              |
| 4     | MEM                 | EX                  | ID (STALL)      |
| 5     | WB                  | MEM                 | STALL           |
| 6     |                     | WB                  | STALL           |
| 7     |                     |                     | EX              |
| 8     |                     |                     | MEM             |
| 9     |                     |                     | WB              |

**Con Forwarding:**

| Ciclo | movl -4(%rbp), %edx | movl -8(%rbp), %eax | addl %edx, %eax |
| ----- | ------------------- | ------------------- | --------------- |
| 1     | IF                  |                     |                 |
| 2     | ID                  | IF                  |                 |
| 3     | EX                  | ID                  | IF              |
| 4     | MEM                 | EX                  | ID (STALL)      |
| 5     | WB                  | MEM                 | EX (Forwarding) |
| 6     |                     | WB                  | MEM             |
| 7     |                     |                     | WB              |

**Mejora:** 2 ciclos ahorrados (9 vs 7 ciclos totales)

---

## Instalación y Configuración

### Requisitos

- Microsoft Excel 2013 o superior
- Macros habilitadas
- Resolución de pantalla recomendada: 1920×1080 o superior

### Pasos de Instalación

1. **Descargar el repositorio:**

   ```bash
   git clone https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86.git
   cd Simulador-de-Arquitectura-x86
   ```

2. **Abrir el archivo Excel:**

   - Localizar `SimuladorX86.xlsm` (o nombre equivalente)
   - Hacer doble clic para abrir

3. **Habilitar macros:**

   - Cuando aparezca la advertencia de seguridad, clic en "Habilitar contenido"
   - Si no aparece, ir a `Archivo → Opciones → Centro de confianza → Configuración del Centro de confianza → Configuración de macros` y seleccionar "Habilitar todas las macros"

4. **Verificar módulos VBA:**
   - Presionar `Alt + F11` para abrir el editor VBA
   - Confirmar que todos los módulos están presentes (Módulo1 a Módulo9)

### Uso Básico

1. **Ingresar código ensamblador:**

   - En `Hoja1`, celda B3 o B5, escribir el código en sintaxis AT&T
   - Ejemplo: `movl $10, %eax`

2. **Cargar el programa:**

   - Ejecutar macro `CargarEnsamblador` (botón o `Alt + F8`)

3. **Ejecutar paso a paso:**

   - Usar `AvanzarCiclo` para ejecutar una instrucción completa (5 etapas)
   - Observar la visualización en tiempo real

4. **Simular pipeline:**

   - Usar `SimularPipelineCPU` para ejecutar múltiples instrucciones con visualización de tabla

5. **Ver memoria y registros:**
   - Los rangos en la hoja se actualizan automáticamente
   - Usar `MostrarMemoriaFormatted` para ver el contenido completo de memoria

---

## 📊 Estadísticas Generales del Proyecto

- **Total de Issues**: 27
- **Issues Cerradas**: 27 (100%)
- **Pull Requests**: 2
- **Período de Desarrollo**: 6 días
- **Duración Total**: 29 septiembre - 5 octubre 2025
- **Etiquetas Utilizadas**: enhancement, documentation

---

## 🗓️ Roadmap Cronológico

### **Fase 1: Fundamentos (Día 1 - 29 Septiembre 2025)**

#### **Sprint 1.1: Componentes Core del CPU**

| #   | Título                                        | Asignado a                | Estado     | Prioridad | Inicio | Cierre |
| --- | --------------------------------------------- | ------------------------- | ---------- | --------- | ------ | ------ |
| #1  | Implementar CPU Base con Registros y Banderas | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |
| #2  | Desarrollar Unidad Aritmético-Lógica (ALU)    | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |
| #3  | Implementar Sistema de Memoria RAM            | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |

**Entregables:**

- Sistema de registros x86 funcional
- ALU con operaciones aritméticas básicas
- Sistema de memoria RAM básico

---

#### **Sprint 1.2: Parser y Motor de Simulación**

| #   | Título                          | Asignado a                | Estado     | Prioridad | Inicio | Cierre |
| --- | ------------------------------- | ------------------------- | ---------- | --------- | ------ | ------ |
| #4  | Crear Parser de Ensamblador x86 | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |
| #5  | Desarrollar Motor de Simulación | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |

**Entregables:**

- Parser de instrucciones ensamblador x86
- Motor de ejecución de instrucciones

---

#### **Sprint 1.3: API y Sistema de Salida**

| #   | Título                             | Asignado a                | Estado     | Prioridad | Inicio | Cierre |
| --- | ---------------------------------- | ------------------------- | ---------- | --------- | ------ | ------ |
| #6  | Desarrollar API para VBA Excel     | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |
| #7  | Implementar Sistema de Salida JSON | @alejandroramirezvallejos | ✅ Cerrado | Alta      | 29/09  | 29/09  |
| #8  | Configurar Sistema de Tipos        | @alejandroramirezvallejos | ✅ Cerrado | Media     | 29/09  | 29/09  |

**Entregables:**

- API DLL para integración con VBA
- Sistema de serialización JSON
- Sistema de tipos de datos

---

### **Fase 2: Interfaz y Características Avanzadas (Días 2-3)**

#### **Sprint 2.1: Interfaz Visual y Generación de Código**

| #   | Título                                       | Asignado a                                  | Estado     | Prioridad | Inicio | Cierre |
| --- | -------------------------------------------- | ------------------------------------------- | ---------- | --------- | ------ | ------ |
| #9  | Desarrollar Interfaz Visual Excel VBA        | @josue-balbontin, @FernandoTerrazasLl       | ✅ Cerrado | Alta      | 29/09  | 03/10  |
| #10 | Implementar Generador C++ a Ensamblador AT&T | @josue-balbontin, @alejandroramirezvallejos | ✅ Cerrado | Media     | 29/09  | 02/10  |

**Entregables:**

- Interfaz gráfica en Excel con VBA
- Generador automático de código ensamblador

---

#### **Sprint 2.2: Sistemas de Memoria Avanzados**

| #   | Título                                       | Asignado a                                     | Estado     | Prioridad | Inicio | Cierre |
| --- | -------------------------------------------- | ---------------------------------------------- | ---------- | --------- | ------ | ------ |
| #11 | Desarrollar Sistema de Memoria Caché con LRU | @alejandroramirezvallejos, @FernandoTerrazasLl | ✅ Cerrado | Alta      | 29/09  | 01/10  |
| #12 | Implementar Pipeline de CPU (4 Etapas)       | @FernandoTerrazasLl                            | ✅ Cerrado | Alta      | 29/09  | 01/10  |
| #13 | Desarrollar Sistema de Entrada/Salida (I/O)  | @FernandoTerrazasLl                            | ✅ Cerrado | Media     | 29/09  | 03/10  |
| #14 | Implementar Memoria Virtual Básica           | @FernandoTerrazasLl                            | ✅ Cerrado | Media     | 29/09  | 01/10  |

**Entregables:**

- Sistema de caché L1/L2 con política LRU
- Pipeline de CPU de 4 etapas
- Sistema básico de I/O
- Memoria virtual con paginación

---

### **Fase 3: Integración y Optimización (Días 4-5)**

#### **Sprint 3.1: Integración Excel-C++**

| #   | Título                                        | Asignado a       | Estado     | Prioridad | Inicio | Cierre |
| --- | --------------------------------------------- | ---------------- | ---------- | --------- | ------ | ------ |
| #15 | Conectar Excel con simulador C++ mediante DLL | @josue-balbontin | ✅ Cerrado | Crítica   | 30/09  | 30/09  |
| #16 | Localización automática del DLL               | @josue-balbontin | ✅ Cerrado | Media     | 30/09  | 30/09  |

**Entregables:**

- Integración completa Excel-DLL
- Carga automática de DLL

---

#### **Sprint 3.2: Documentación y Mejoras**

| #   | Título                                         | Asignado a       | Estado     | Prioridad | Inicio | Cierre |
| --- | ---------------------------------------------- | ---------------- | ---------- | --------- | ------ | ------ |
| #18 | Documentar relaciones del ciclo de instrucción | @josue-balbontin | ✅ Cerrado | Baja      | 30/09  | 30/09  |
| #19 | Automatizar gestión de memoria RAM/virtual     | @josue-balbontin | ✅ Cerrado | Media     | 30/09  | 30/09  |

**Entregables:**

- Documentación técnica del ciclo de instrucciones
- Mejora en la gestión de memoria

---

### **Fase 4: Características Avanzadas (Días 5-6)**

#### **Sprint 4.1: Visualización de Memoria**

| #   | Título                                        | Asignado a          | Estado     | Prioridad | Inicio | Cierre |
| --- | --------------------------------------------- | ------------------- | ---------- | --------- | ------ | ------ |
| #20 | Desarrollar interfaz para Memoria RAM/Virtual | @FernandoTerrazasLl | ✅ Cerrado | Media     | 30/09  | 01/10  |
| #21 | Comparativa Von Neumann y Harvard             | @FernandoTerrazasLl | ✅ Cerrado | Alta      | 30/09  | 01/10  |

**Entregables:**

- Visualización avanzada de RAM/Memoria Virtual
- Comparación visual de arquitecturas

---

#### **Sprint 4.2: Ejecución de Código**

| #   | Título                                     | Asignado a       | Estado     | Prioridad | Inicio | Cierre |
| --- | ------------------------------------------ | ---------------- | ---------- | --------- | ------ | ------ |
| #22 | Ejecución de código ensamblador en DLL C++ | @josue-balbontin | ✅ Cerrado | Crítica   | 01/10  | 02/10  |

**Entregables:**

- Sistema de ejecución de código ensamblador
- Sistema de debugging
- Mejoras en el formato JSON

---

### **Fase 5: Refinamiento Final (Días 6-7)**

#### **Sprint 5.1: Optimizaciones Finales**

| #   | Título                                                         | Asignado a                            | Estado     | Prioridad | Inicio | Cierre |
| --- | -------------------------------------------------------------- | ------------------------------------- | ---------- | --------- | ------ | ------ |
| #24 | Gestión dinámica registros x86-64                              | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Alta      | 03/10  | 03/10  |
| #25 | Visualización pipeline paso a paso                             | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Alta      | 03/10  | 03/10  |
| #26 | Caché mejorada con política LRU                                | @FernandoTerrazasLl                   | ✅ Cerrado | Alta      | 03/10  | 03/10  |
| #27 | Instrucciones aritméticas (MOV, ADD, SUB, MUL, DIV, PUSH, POP) | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Crítica   | 03/10  | 03/10  |

**Entregables:**

- Sistema de registros dinámicos x86-64
- Visualización mejorada del pipeline
- Caché optimizada con LRU
- Conjunto completo de instrucciones aritméticas

---

## 📈 Análisis de Distribución de Trabajo

### Por Desarrollador

| Desarrollador             | Issues Asignadas | Issues Individuales | Issues en Colaboración |
| ------------------------- | ---------------- | ------------------- | ---------------------- |
| @alejandroramirezvallejos | 11               | 9                   | 2                      |
| @josue-balbontin          | 10               | 5                   | 5                      |
| @FernandoTerrazasLl       | 10               | 5                   | 5                      |

### Por Tipo de Tarea

| Categoría     | Cantidad | Porcentaje |
| ------------- | -------- | ---------- |
| Backend/Core  | 14       | 51.9%      |
| Interfaz/UI   | 5        | 18.5%      |
| Integración   | 4        | 14.8%      |
| Documentación | 2        | 7.4%       |
| Pull Requests | 2        | 7.4%       |

---

## 🏷️ Historias de Usuario

### Historia de Usuario 1: Simulación Básica

**Como** estudiante de arquitectura de computadoras  
**Quiero** ejecutar código ensamblador x86 en un simulador visual  
**Para** entender cómo funciona la CPU a bajo nivel

**Issues Relacionadas:** #1, #2, #4, #5, #22, #27

---

### Historia de Usuario 2: Visualización de Memoria

**Como** profesor de sistemas operativos  
**Quiero** visualizar la jerarquía de memoria (RAM, Caché, Virtual)  
**Para** explicar conceptos de gestión de memoria a mis estudiantes

**Issues Relacionadas:** #3, #11, #14, #20, #26

---

### Historia de Usuario 3: Análisis de Pipeline

**Como** investigador de arquitectura de computadoras  
**Quiero** ver la ejecución paso a paso del pipeline  
**Para** analizar el comportamiento de las instrucciones

**Issues Relacionadas:** #12, #25

---

### Historia de Usuario 4: Interfaz Amigable

**Como** usuario sin experiencia en programación  
**Quiero** una interfaz visual intuitiva en Excel  
**Para** interactuar fácilmente con el simulador

**Issues Relacionadas:** #9, #15, #16

---

### Historia de Usuario 5: Comparación de Arquitecturas

**Como** estudiante avanzado  
**Quiero** comparar arquitecturas Von Neumann y Harvard  
**Para** comprender sus diferencias fundamentales

**Issues Relacionadas:** #21

---

## 📊 Métricas del Proyecto

### Velocidad de Desarrollo

- **Promedio de issues cerradas por día:** 4.5
- **Tiempo promedio de resolución:** 0.8 días
- **Tasa de finalización:** 100%

### Complejidad

- **Issues Alta Prioridad:** 14 (51.9%)
- **Issues Media Prioridad:** 8 (29.6%)
- **Issues Baja Prioridad:** 1 (3.7%)
- **Pull Requests:** 2 (7.4%)

### Colaboración

- **Issues individuales:** 19 (70.4%)
- **Issues en equipo (2+ personas):** 8 (29.6%)

---

## 🎯 Backlog Priorizado

### Prioridad Crítica ✅ (COMPLETADO)

1. #15 - Integración Excel-DLL
2. #22 - Ejecución de código ensamblador
3. #27 - Instrucciones aritméticas completas

### Prioridad Alta ✅ (COMPLETADO)

1. #1 - CPU Base
2. #2 - ALU
3. #3 - Memoria RAM
4. #4 - Parser
5. #5 - Motor de Simulación
6. #6 - API VBA
7. #9 - Interfaz Visual
8. #11 - Sistema de Caché
9. #12 - Pipeline CPU
10. #21 - Comparación de Arquitecturas
11. #24 - Registros Dinámicos
12. #25 - Visualización Pipeline
13. #26 - Caché Mejorada

### Prioridad Media ✅ (COMPLETADO)

1. #8 - Sistema de Tipos
2. #10 - Generador C++ a Ensamblador
3. #13 - Sistema I/O
4. #14 - Memoria Virtual
5. #16 - Carga Automática DLL
6. #19 - Gestión Memoria
7. #20 - Interfaz RAM/Virtual

### Prioridad Baja ✅ (COMPLETADO)

1. #18 - Documentación

---

## 📝 Notas Adicionales

### Etiquetas Utilizadas

- **enhancement**: Mejoras y nuevas características (8 issues)
- **documentation**: Documentación técnica (2 issues)

### Observaciones

1. El proyecto se completó exitosamente en 6 días
2. Todos los miembros del equipo contribuyeron activamente
3. La mayoría de las issues se cerraron el mismo día de su creación
4. Se utilizó una estrategia de desarrollo ágil con entregas rápidas
5. El enfoque fue en componentes core primero, luego integración y finalmente optimización

---

## Referencias

### Literatura Académica

1. **Patterson, D. A., & Hennessy, J. L.** (2017). _Computer Organization and Design: The Hardware/Software Interface_ (5th ed.). Morgan Kaufmann.

   - Capítulos 4 (El procesador) y 5 (Jerarquía de memoria)

2. **Hennessy, J. L., & Patterson, D. A.** (2019). _Computer Architecture: A Quantitative Approach_ (6th ed.). Morgan Kaufmann.

   - Secciones sobre pipeline y hazards

3. **Stallings, W.** (2015). _Computer Organization and Architecture: Designing for Performance_ (10th ed.). Pearson.

   - Capítulos sobre arquitectura de CPU y memoria

4. **Tanenbaum, A. S., & Austin, T.** (2013). _Structured Computer Organization_ (6th ed.). Pearson.
   - Análisis de arquitecturas Von Neumann vs. Harvard

### Recursos en Línea

- [Intel® 64 and IA-32 Architectures Software Developer's Manual](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
- [AT&T Assembly Syntax](https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax)
- [CPU Pipeline Visualization](https://www.scss.tcd.ie/~jones/CS2011/pipeline.html)

## Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el repositorio
2. Crear una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abrir un Pull Request

---

## Autores

- [Josue Galo Balbontin Ugarteche](https://github.com/josue-balbontin)
- [Alejandro Ramirez Vallejos](https://github.com/alejandroramirezvallejos)
- [Fernando Terrazas Llanos](https://github.com/FernandoTerrazasLl)

---

## Repositorio

- GitHub: [@alejandroramirezvallejos](https://github.com/alejandroramirezvallejos)
- Repositorio: [Simulador-de-Arquitectura-x86](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)
