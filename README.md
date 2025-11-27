# Simulador de Arquitectura x86

[![Excel VBA](https://img.shields. io/badge/Excel_VBA-100%25-217346? logo=microsoftexcel)](https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86)
[![Architecture](https://img.shields.io/badge/Architecture-Von_Neumann-blue)](https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-orange.svg)](https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86)
[![Status](https://img.shields.io/badge/Status-Complete-success)](https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86)

---

## 📋 Descripción General

Simulador interactivo de arquitectura x86 desarrollado en **Excel con VBA**. Esta herramienta educativa permite visualizar y comprender el funcionamiento interno de un procesador moderno mediante la ejecución paso a paso de instrucciones en ensamblador.

El simulador implementa una **arquitectura Von Neumann**, donde instrucciones y datos comparten el mismo espacio de memoria, facilitando la comprensión de conceptos fundamentales de arquitectura de computadoras.

**Repositorio:** [https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86](https://github. com/alejandroramirezucb/Simulador-de-Arquitectura-x86)

---

## 📑 Tabla de Contenidos

### **1. [Introducción](#-introducción)**

- 1.1 [Descripción General](#11-descripción-general)
- 1.2 [Objetivos del Proyecto](#12-objetivos-del-proyecto)
- 1.3 [Características Principales](#13-características-principales)

### **2. [Fundamentos Teóricos](#-fundamentos-teóricos)**

- 2.1 [Unidad de Control](#21-unidad-de-control-control-unit)
- 2.2 [Unidad Aritmético-Lógica (ALU)](#22-unidad-aritmético-lógica-alu)
- 2.3 [Banco de Registros](#23-banco-de-registros-registers)
- 2.4 [Unidad de Memoria](#24-unidad-de-memoria-memory-unit)
- 2.5 [Memoria Virtual](#25-memoria-virtual)
- 2.6 [Memoria Caché](#26-memoria-caché)
- 2.7 [Arquitectura Von Neumann](#27-arquitectura-von-neumann)
- 2.8 [Ciclo de Instrucción](#28-ciclo-de-instrucción)
- 2.9 [Pipeline de Instrucciones](#29-pipeline-de-instrucciones)
- 2.10 [Manejo de Interrupciones y E/S](#210-manejo-de-interrupciones-y-entradasalida-io)

### **3. [Arquitectura del Simulador](#-arquitectura-del-simulador)**

- 3.1 [Visión de Alto Nivel](#31-visión-de-alto-nivel)
- 3.2 [Componentes del Sistema](#32-componentes-del-sistema)
- 3.3 [Flujo de Datos](#33-flujo-de-datos-end-to-end)

### **4. [Decisiones de Diseño](#-decisiones-de-diseño)**

- 4.1 [Elección de Plataforma](#41-elección-de-plataforma-excel--vba)
- 4. 2 [Arquitectura Von Neumann](#42-arquitectura-von-neumann)
- 4.3 [Pipeline de 5 Etapas](#43-pipeline-de-5-etapas)
- 4. 4 [Gestión Dinámica de Registros](#44-gestión-dinámica-de-registros)
- 4.5 [Simulación de Memoria](#45-simulación-de-memoria-con-dictionary)
- 4.6 [Política de Caché LRU](#46-política-de-caché-lru)
- 4.7 [Visualización en Tiempo Real](#47-visualización-en-tiempo-real)

### **5. [Componentes Implementados](#-componentes-implementados)**

- 5.1 [Listado de Módulos VBA](#51-listado-de-módulos-vba)
- 5.2 [Estructuras de Datos](#52-estructuras-de-datos-principales)

### **6. [Manejo de Hazards](#-manejo-de-hazards-y-dependencias)**

- 6.1 [Tipos de Hazards](#61-tipos-de-hazards)
- 6.2 [Políticas de Mitigación](#62-políticas-de-mitigación)
- 6.3 [Visualización de Hazards](#63-visualización-de-hazards)

### **7. [Guía de Uso](#-guía-de-uso-detallada)**

- 7. 1 [Requisitos del Sistema](#71-requisitos-del-sistema)
- 7. 2 [Instalación](#72-instalación)
- 7.3 [Uso Básico](#73-uso-básico)
- 7.4 [Funciones Avanzadas](#74-funciones-avanzadas)
- 7.5 [Solución de Problemas](#75-solución-de-problemas)

### **8. [Ejemplos Prácticos](#-ejemplos-prácticos)**

- 8.1 [Ejemplo Completo](#81-ejemplo-completo-suma-de-dos-números)
- 8.2 [Tabla Pipeline con Hazards](#82-tabla-pipeline-con-hazards)

### **9. [Referencias](#-referencias)**

### **10. [Apéndices](#-apéndices)**

- A. [Convenciones de Nomenclatura](#apéndice-a-convenciones-de-nomenclatura)
- B. [Conjunto de Instrucciones](#apéndice-b-conjunto-completo-de-instrucciones-soportadas)

### **111. [Licencia y Autores](#-licencia-y-autores)**

---

## 🎯 Introducción

### 1.1 Descripción General

El Simulador de Arquitectura x86 es una herramienta educativa desarrollada completamente en **Microsoft Excel con Visual Basic for Applications (VBA)**. Su objetivo principal es proporcionar una plataforma visual e interactiva para comprender el funcionamiento de un procesador x86 moderno.

El simulador permite ejecutar código ensamblador en sintaxis AT&T, visualizando en tiempo real el comportamiento del procesador a través de sus componentes principales: unidad de control, ALU, registros, memoria y sistema de caché.

### 1.2 Objetivos del Proyecto

1. **Educación Visual**: Proporcionar una representación gráfica del funcionamiento interno de un procesador
2. **Comprensión del Pipeline**: Facilitar el entendimiento de la ejecución superpuesta de instrucciones
3. **Análisis de Hazards**: Mostrar las dependencias entre instrucciones y sus soluciones
4. **Gestión de Memoria**: Ilustrar la jerarquía de memoria (registros, caché, RAM, memoria virtual)
5. **Accesibilidad**: Utilizar una plataforma familiar (Excel) para reducir la curva de aprendizaje

### 1.3 Características Principales

| Característica           | Descripción                                             |
| ------------------------ | ------------------------------------------------------- |
| **Arquitectura**         | Von Neumann (memoria unificada)                         |
| **Plataforma**           | Microsoft Excel con macros VBA                          |
| **Sintaxis Soportada**   | AT&T Assembly (x86-64)                                  |
| **Pipeline**             | 5 etapas (IF, ID, EX, MEM, WB)                          |
| **Registros**            | 16 registros de propósito general (RAX-R15)             |
| **Memoria**              | Jerarquía completa: L1 I-Cache, L1 D-Cache, L2, L3, RAM |
| **Instrucciones**        | MOV, ADD, SUB, MUL, DIV, PUSH, POP, CMP, JMP            |
| **Detección de Hazards** | RAW, WAW, WAR con inserción automática de stalls        |
| **Visualización**        | Colores dinámicos y animaciones en tiempo real          |

---

## 📚 Fundamentos Teóricos

### 2.1 Unidad de Control (Control Unit)

#### 2.1.1 Conceptualización

La Unidad de Control (UC) actúa como el orquestador del procesador, coordinando todas las operaciones mediante señales de control que activan los componentes apropiados en el momento correcto.

**Responsabilidades principales:**

1. **Secuenciación**: Mantener el orden correcto de ejecución
2. **Temporización**: Generar señales de reloj
3. **Decodificación**: Interpretar instrucciones
4. **Coordinación**: Sincronizar ALU, memoria y registros

#### 2.1. 2 Componentes

```
┌─────────────────────────────────────────────┐
│         UNIDAD DE CONTROL                   │
├─────────────────────────────────────────────┤
│  ┌──────────────────────────────────────┐  │
│  │  Program Counter (PC)                │  │
│  │  • Apunta a la siguiente instrucción │  │
│  │  • Tamaño: 64 bits                   │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Instruction Register (IR)           │  │
│  │  • Almacena instrucción actual       │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Memory Address Register (MAR)       │  │
│  │  • Dirección a acceder en memoria    │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Memory Data Register (MDR)          │  │
│  │  • Dato a leer/escribir              │  │
│  └──────────────────────────────────────┘  │
└─────────────────────────────────────────────┘
```

#### 2.1.3 Diseño en el Simulador

**Representación Visual:**

- **PC**: Celda CELDA_PC muestra la dirección actual en hexadecimal
- **IR**: Shape R. I contiene la instrucción en ejecución
- **MAR**: Celda CELDA_MAR durante accesos a memoria
- **MDR**: Celda CELDA_MDR durante transferencias

**Implementación VBA:**

```vba
' Variable global para Program Counter
Public PC As Long

Sub InicializarUnidadControl()
    PC = 0
    CELDA_PC. Value = "0x" & Hex(PC)
    CELDA_IR.Value = ""
End Sub

Sub IncrementarPC()
    PC = PC + 1
    CELDA_PC.Value = "0x" & Hex(PC)
    Call ResaltarTemporal(CELDA_PC, COLOR_ACTIVO, 0. 5)
End Sub
```

---

### 2.2 Unidad Aritmético-Lógica (ALU)

#### 2.2.1 Conceptualización

La ALU es el núcleo computacional del procesador, realizando todas las operaciones aritméticas y lógicas sobre datos binarios.

**Características fundamentales:**

1. **Operaciones Aritméticas**: Suma, resta, multiplicación, división
2. **Operaciones Lógicas**: AND, OR, XOR, NOT
3. **Comparaciones**: CMP (resta sin almacenar resultado)
4. **Actualización de Flags**: ZF, SF, CF, OF según el resultado

#### 2.2. 2 Operaciones Soportadas

| Instrucción | Sintaxis          | Operación           | Flags Afectados | Ciclos |
| ----------- | ----------------- | ------------------- | --------------- | ------ |
| **MOV**     | `movl src, dest`  | dest = src          | Ninguno         | 1      |
| **ADD**     | `addl src, dest`  | dest = dest + src   | ZF, SF, CF, OF  | 1      |
| **SUB**     | `subl src, dest`  | dest = dest - src   | ZF, SF, CF, OF  | 1      |
| **MUL**     | `mull src`        | RDX:RAX = RAX × src | CF, OF          | 3-4    |
| **AND**     | `andl src, dest`  | dest = dest & src   | ZF, SF          | 1      |
| **OR**      | `orl src, dest`   | dest = dest \| src  | ZF, SF          | 1      |
| **CMP**     | `cmpl src1, src2` | temp = src2 - src1  | ZF, SF, CF, OF  | 1      |

**Descripción de Flags:**

- **ZF (Zero Flag)**: Se activa si el resultado es cero
- **SF (Sign Flag)**: Se activa si el resultado es negativo
- **CF (Carry Flag)**: Se activa en overflow sin signo
- **OF (Overflow Flag)**: Se activa en overflow con signo

---

### 2.3 Banco de Registros (Registers)

#### 2.3. 1 Conceptualización

Los registros son la memoria más rápida del procesador, ubicados dentro del chip de la CPU.

**Características:**

- **Velocidad**: Acceso en < 1 ciclo de reloj
- **Tamaño**: 64 bits en x86-64 (compatibles con 32, 16, 8 bits)
- **Cantidad**: 16 registros de propósito general
- **Acceso**: Lectura/escritura simultánea

#### 2.3.2 Jerarquía de Registros x86-64

```
┌────────────┬──────────┬──────────┬──────────────┐
│  64-bit    │  32-bit  │  16-bit  │    8-bit     │
├────────────┼──────────┼──────────┼──────────────┤
│  RAX       │  EAX     │  AX      │  AH    AL    │
│  RBX       │  EBX     │  BX      │  BH    BL    │
│  RCX       │  ECX     │  CX      │  CH    CL    │
│  RDX       │  EDX     │  DX      │  DH    DL    │
│  RSI       │  ESI     │  SI      │         SIL  │
│  RDI       │  EDI     │  DI      │         DIL  │
│  RBP       │  EBP     │  BP      │         BPL  │
│  RSP       │  ESP     │  SP      │         SPL  │
│  R8        │  R8D     │  R8W     │         R8B  │
│  R9-R15    │  R9D-R15D│  R9W-R15W│       R9B-R15B│
└────────────┴──────────┴──────────┴──────────────┘
```

#### 2.3.3 Diseño en el Simulador

**Sistema de Normalización:**

```vba
Function NormalizarNombreRegistro(regRaw As String) As String
    Dim reg As String
    reg = UCase(Trim(Replace(regRaw, "%", "")))

    Select Case reg
        Case "EAX": NormalizarNombreRegistro = "RAX"
        Case "EBX": NormalizarNombreRegistro = "RBX"
        Case "AX": NormalizarNombreRegistro = "RAX"
        Case "AL", "AH": NormalizarNombreRegistro = "RAX"
        Case Else: NormalizarNombreRegistro = reg
    End Select
End Function
```

**Gestión Dinámica:**

```vba
Public registrosDict As Object

Sub InicializarSistemaRegistros()
    Set registrosDict = CreateObject("Scripting.Dictionary")

    ' Registros básicos
    registrosDict.Add "RAX", 0&
    registrosDict.Add "RBX", 0&
    registrosDict.Add "RSP", &H7FFFFFFFE000

    Call DetectarRegistrosEnCodigo
    Call RenderizarRegistrosEnExcel
End Sub
```

---

### 2. 7 Arquitectura Von Neumann

#### 2.7.1 Conceptualización

La arquitectura Von Neumann se caracteriza por el uso de una **memoria unificada** que almacena tanto instrucciones como datos.

**Principios fundamentales:**

1. **Stored-Program Concept**: Las instrucciones se almacenan en memoria como datos
2. **Memoria Unificada**: Un único espacio de direcciones
3. **Bus Compartido**: El mismo canal para instrucciones y datos
4. **Secuencialidad**: Ejecución secuencial salvo saltos

#### 2.7. 2 Características Principales

```
┌──────────────────────────────────────────────┐
│                   CPU                        │
│  ┌────────────┐       ┌─────────────┐       │
│  │  Unidad de │◄─────►│     ALU     │       │
│  │   Control  │       │             │       │
│  └─────┬──────┘       └─────────────┘       │
│        │                                     │
│  ┌─────▼──────────────────────────┐         │
│  │     Banco de Registros         │         │
│  └────────────────────────────────┘         │
└────────────┬─────────────────────────────────┘
             │ BUS ÚNICO
             │
┌────────────▼─────────────────────────────────┐
│           MEMORIA UNIFICADA                  │
│  ┌──────────────────┬──────────────────┐    │
│  │   Instrucciones  │      Datos       │    │
│  └──────────────────┴──────────────────┘    │
└──────────────────────────────────────────────┘
```

#### 2.7.3 Ventajas y Desventajas

**✅ VENTAJAS:**

- Simplicidad de diseño hardware
- Flexibilidad en distribución de memoria
- Menor costo de implementación

**❌ DESVENTAJAS:**

- Cuello de botella de Von Neumann (bus compartido)
- Acceso secuencial (no simultáneo)
- Menor throughput comparado con Harvard

---

### 2.8 Ciclo de Instrucción

#### 2.8.1 Conceptualización

El ciclo de instrucción es la secuencia completa de microoperaciones para ejecutar una única instrucción.

**Fases:**

1. **IF (Instruction Fetch)**: Obtener instrucción de memoria
2. **ID (Instruction Decode)**: Decodificar e identificar operandos
3. **EX (Execute)**: Ejecutar operación en ALU
4. **MEM (Memory Access)**: Acceder a memoria si necesario
5. **WB (Write Back)**: Escribir resultados en registros

#### 2.8.2 Implementación

```vba
Sub AvanzarCiclo()
    Debug.Print "=== CICLO " & (PC + 1) & " ==="

    ' Etapa 1: FETCH
    Call Fetch()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' Etapa 2: DECODE
    Call Decode()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' Etapa 3: EXECUTE
    Call Execute()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' Etapa 4: MEMORY ACCESS
    Call MemoryAccess()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' Etapa 5: WRITE BACK
    Call WriteBack()
    Application.Wait (Now + TimeValue("0:00:00.5"))
End Sub
```

---

### 2.9 Pipeline de Instrucciones

#### 2.9.1 Conceptualización

El pipeline permite la ejecución superpuesta de múltiples instrucciones, donde cada etapa trabaja en una instrucción diferente simultáneamente.

**Analogía:**

```
SIN PIPELINE:
I1: [IF][ID][EX][MEM][WB]
I2:                      [IF][ID][EX][MEM][WB]
Total: 10 ciclos para 2 instrucciones

CON PIPELINE:
Ciclo: 1    2    3    4    5    6
I1:   [IF][ID][EX][MEM][WB]
I2:       [IF][ID][EX][MEM][WB]
Total: 6 ciclos para 2 instrucciones
```

#### 2.9.2 Beneficios

- **Mayor Throughput**: 1 instrucción por ciclo en estado estable
- **Mejor Utilización**: Todas las unidades trabajan simultáneamente
- **Speedup Teórico**: Hasta 5× con pipeline de 5 etapas

---

### 2.10 Manejo de Interrupciones y Entrada/Salida (I/O)

El simulador incluye un módulo de E/S con manejo de interrupciones que opera dentro de la arquitectura Von Neumann.

#### 2.10.1 Flujo del Proceso

1. **Entrada de Usuario**: Comando en la Terminal
2. **Búfer de Teclado**: Transferencia carácter a carácter
3. **Cola de Ejecución**: Solicitud de interrupción
4. **ISR (Interrupt Service Routine)**: Procesamiento del comando
5. **Búfer de Pantalla**: Generación de salida
6. **Visualización**: Renderizado en pantalla

#### 2.10.2 Componentes

```vba
' Búfer de Teclado
Public Const BUFFER_TECLADO_FILA_INICIO As Long = 20

' Búfer de Pantalla
Public Const BUFFER_PANTALLA_FILA As Long = 60

' Cola de ejecución
Public colaEjecucion As Collection

Sub BotonEnviar()
    Dim cmd As String
    cmd = Trim$(ws.Range("CELDA_TERMINAL_INPUT").Value)
    If cmd <> "" Then
        Call AgregarABufferTeclado(cmd)
    End If
End Sub
```

---

## 🏗️ Arquitectura del Simulador

### 3.1 Visión de Alto Nivel

El simulador está estructurado en tres capas:

```
╔════════════════════════════════════════════════╗
║    CAPA DE PRESENTACIÓN (Excel UI)             ║
╠════════════════════════════════════════════════╣
║  • Hojas de cálculo                           ║
║  • Shapes y objetos gráficos                  ║
║  • Tablas de visualización                    ║
╚════════════════════════════════════════════════╝
                    ↕
╔════════════════════════════════════════════════╗
║    CAPA DE CONTROL (VBA Modules)               ║
╠════════════════════════════════════════════════╣
║  • 9 módulos VBA (~2,850 líneas)              ║
║  • Lógica de simulación                       ║
║  • Gestión de eventos                         ║
╚════════════════════════════════════════════════╝
                    ↕
╔════════════════════════════════════════════════╗
║    CAPA DE DATOS (Almacenamiento)              ║
╠════════════════════════════════════════════════╣
║  • Dictionaries (memoria, registros)          ║
║  • Variables globales (PC, Flags)             ║
╚════════════════════════════════════════════════╝
```

---

### 3.2 Componentes del Sistema

#### 3.2. 1 Estructura de Hojas

| Hoja             | Propósito            | Contenido                               |
| ---------------- | -------------------- | --------------------------------------- |
| **Hoja1**        | Entrada de código    | Celda B3: código ensamblador            |
| **Hoja2**        | Simulación principal | Código normalizado, registros, pipeline |
| **Memoria**      | Visualización de RAM | Tabla con direcciones y valores         |
| **Arquitectura** | Diagrama educativo   | Representación gráfica Von Neumann      |

---

### 3.3 Flujo de Datos End-to-End

```
1.  ENTRADA
   ↓ Usuario escribe código AT&T en Hoja1

2. CARGA
   ↓ Botón "Cargar Ensamblador"

3. NORMALIZACIÓN
   ↓ Limpiar y copiar a Hoja2

4. INICIALIZACIÓN
   ↓ Crear estructuras de datos

5.  EJECUCIÓN
   ↓ Ciclo de instrucción / Pipeline

6. ACTUALIZACIÓN
   ↓ Registros, memoria, cachés

7. VISUALIZACIÓN
   ↓ Excel refleja cambios con colores
```

---

## 💡 Decisiones de Diseño

### 4.1 Elección de Plataforma: Excel + VBA

**Justificación:**

✅ **Accesibilidad Universal**: Disponible en instituciones educativas
✅ **Visualización Nativa**: Celdas como memoria visual
✅ **Curva de Aprendizaje**: VBA más simple que C++/Java
✅ **Prototipado Rápido**: Cambios inmediatos sin compilación

**Limitaciones Aceptadas:**
❌ Rendimiento menor que lenguajes compilados
❌ No escalable para simulaciones grandes

---

### 4.2 Arquitectura Von Neumann

**Justificación:**

✅ Modelo educativo clásico enseñado universalmente
✅ Representación realista de sistemas x86
✅ Implementación más simple que Harvard
✅ Muestra el cuello de botella del bus compartido

---

### 4.3 Pipeline de 5 Etapas

**Justificación:**

✅ Estándar RISC (MIPS, ARM)
✅ Balance entre complejidad y realismo
✅ Visualización clara en Excel
✅ Suficiente para demostrar hazards

---

### 4.4 Gestión Dinámica de Registros

**Justificación:**

✅ Reducción de ruido visual (solo registros usados)
✅ Escalabilidad (2 o 16 registros)
✅ Detección automática con regex

---

### 4.5 Simulación de Memoria con Dictionary

**Justificación:**

✅ Búsqueda O(1) mediante hash table
✅ Memoria dispersa (solo direcciones usadas)
✅ Legibilidad en debugging ("MEM_0x1000")

---

### 4.6 Política de Caché LRU

**Justificación:**

✅ Intuitiva ("eliminar el menos usado recientemente")
✅ Buen hit rate en mayoría de casos
✅ Simple de implementar en Excel

---

### 4.7 Visualización en Tiempo Real

**Justificación:**

✅ Efecto didáctico (ver flujo de datos)
✅ Identificación visual de hazards
✅ Velocidad configurable según nivel del estudiante

```vba
Sub ResaltarTemporal(rango As Range, color As Long, segundos As Double)
    rango.Interior.Color = color
    Application.Wait (Now + TimeValue("0:00:0" & segundos))
    rango.Interior.ColorIndex = xlNone
End Sub
```

---

## 🔧 Componentes Implementados

### 5.1 Listado de Módulos VBA

| Módulo      | Archivo               | Líneas | Funciones Principales                                     |
| ----------- | --------------------- | ------ | --------------------------------------------------------- |
| **Módulo1** | Pipeline_Visual. bas  | ~300   | `CrearDiagramaPipeline`, `CrearFlechaForwarding`          |
| **Módulo2** | Motor_Simulacion.bas  | ~400   | `SimularPipelineCPU`, `DetectarHazard`                    |
| **Módulo3** | Sistema_Registros.bas | ~350   | `LeerRegistro`, `EscribirRegistro`                        |
| **Módulo4** | ALU_Operaciones.bas   | ~500   | `EjecutarEnALU`, `ActualizarFlags`                        |
| **Módulo5** | Gestion_Memoria.bas   | ~250   | `LeerMemoria`, `EscribirMemoria`                          |
| **Módulo6** | Sistema_Cache.bas     | ~200   | `BuscarEnCache`, `CargarEnCache`                          |
| **Módulo7** | Unidad_Control.bas    | ~400   | `Fetch`, `Decode`, `Execute`, `MemoryAccess`, `WriteBack` |
| **Módulo8** | Parser_ATT.bas        | ~300   | `ParsearInstruccionDirecta`, `ParsearOperando`            |
| **Módulo9** | Utilidades.bas        | ~150   | `ResaltarTemporal`, `LimpiarMemoria`                      |

**Total:** ~2,850 líneas de código VBA

---

### 5. 2 Estructuras de Datos Principales

**memoriaStackGlobal (Scripting.Dictionary)**

- Almacena toda la memoria del sistema
- Claves: "MEM_0x..." (string)
- Valores: Long

**registrosDict (Scripting.Dictionary)**

- Contiene todos los registros normalizados a 64 bits
- Inicialización dinámica

**Variables Globales:**

- `PC As Long`: Program Counter
- `Z1, Z2 As Long`: Registros temporales de resultado
- `ZF, SF, CF, OF As Integer`: Flags del procesador

---

## ⚠️ Manejo de Hazards y Dependencias

### 6. 1 Tipos de Hazards

#### RAW (Read After Write) - El Más Común

```assembly
movl $10, %eax    # I1: Escribe EAX
addl %eax, %ebx   # I2: Lee EAX antes que I1 complete WB
```

**Detección:**

```vba
Function DetectarHazard(instrActual, instrEX, instrMEM) As Boolean
    If InStr(instrActual. registrosFuente, instrEX. RegistroDestino) > 0 Then
        DetectarHazard = True
    End If
End Function
```

---

### 6.2 Políticas de Mitigación

#### Stalling (Inserción de Burbujas)

```vba
Sub InsertarStall(instr As InstruccionPipeline, tabla As Range, ciclo As Long)
    tabla.Cells(ciclo + 1, numInstr + 1). Value = "STALL"
    tabla. Cells(ciclo + 1, numInstr + 1). Interior.Color = RGB(255, 255, 0)
End Sub
```

#### Forwarding/Bypassing

```vba
Sub CrearFlechaForwarding(ws As Worksheet, x1, y1, x2, y2)
    With ws. Shapes.AddConnector(msoConnectorElbow, x1, y1, x2, y2)
        .Line. ForeColor.RGB = RGB(255, 0, 0)
        .Line.Weight = 2
    End With
End Sub
```

---

### 6.3 Visualización de Hazards

**Código de Colores:**

| Color       | Significado              | RGB                |
| ----------- | ------------------------ | ------------------ |
| 🟡 Amarillo | STALL (hazard detectado) | RGB(255, 255, 0)   |
| ⚪ Gris     | BUBBLE (ciclo perdido)   | RGB(200, 200, 200) |
| 🔴 Rojo     | Forwarding activo        | RGB(255, 0, 0)     |
| 🟢 Verde    | Instrucción completada   | RGB(144, 238, 144) |
| 🔵 Azul     | Instrucción en ejecución | RGB(173, 216, 230) |

---

## 📖 Guía de Uso Detallada

### 7.1 Requisitos del Sistema

**Software:**

- Microsoft Excel 2013 o superior
- Windows 7/8/10/11
- Macros habilitadas

---

### 7.2 Instalación

#### 7.2.1 Descargar el Repositorio

```bash
# Opción 1: Clonar con Git
git clone https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86.git

# Opción 2: Descargar ZIP desde GitHub
```

#### 7.2.2 Configurar Excel

1.  Abrir el archivo `EXAMEN 1. xlsm`
2.  Si aparece advertencia de seguridad: **"Habilitar contenido"**
3.  Verificar macros: `Alt + F11` → Ver módulos

---

### 7.3 Uso Básico

#### 7.3.1 Cargar Código Ensamblador

1. Ir a **Hoja1**
2. En celda **B3**, escribir código AT&T:

```assembly
pushq %rbp
movq %rsp, %rbp
movl $9, -4(%rbp)
movl $11, -8(%rbp)
addl %eax, %edx
leave
ret
```

3.  Clic en **"Cargar"**
4.  Confirmar mensaje "Código cargado exitosamente"

#### 7. 3.2 Ejecutar Paso a Paso

1. Ir a **Hoja2**
2. Clic en **"Avanzar Ciclo"**
3. Observar:

- PC incrementándose
- IR con instrucción actual
- Registros actualizándose

#### 7.3.3 Simular Pipeline Completo

1. Clic en **"Simular Pipeline"**
2. Ver tabla ciclo-a-ciclo automática
3. Observar STALLs con colores amarillos
4. Mensaje final con estadísticas

---

### 7.4 Funciones Avanzadas

#### 7.4.1 Configurar Velocidad de Simulación

Editar en VBA:

```vba
Application.Wait (Now + TimeValue("0:00:00.5"))
'                                        ^^^
' Cambiar a 0.1 para más rápido
' Cambiar a 2.0 para más lento
```

#### 7.4. 2 Exportar Resultados

```vba
Sub ExportarMemoria()
    Dim fso, archivo
    Set fso = CreateObject("Scripting.FileSystemObject")
    Set archivo = fso. CreateTextFile("memoria. txt", True)

    For Each clave In memoriaStackGlobal. Keys
        archivo.WriteLine clave & " = " & memoriaStackGlobal(clave)
    Next
    archivo.Close
End Sub
```

---

### 7.5 Solución de Problemas

#### 7.5.1 Errores Comunes

**"Variable no definida"**

- **Causa**: Falta inicialización
- **Solución**: Verificar `memoriaStackGlobal` y `registrosDict`

**"Índice fuera del intervalo"**

- **Causa**: Acceso a celda inexistente
- **Solución**: Verificar rangos nombrados

#### 7.5.2 Debugging

Presionar `Alt + F11` → Ver → Ventana Inmediato (`Ctrl+G`):

```vba
?  PC                           ' Ver valor de PC
? registrosDict("RAX")         ' Valor de RAX
? Range("CELDA_PC").Value      ' Valor en celda
```

---

## 💻 Ejemplos Prácticos

### 8. 1 Ejemplo Completo: Suma de Dos Números

```assembly
# main.s - Suma dos números

pushq %rbp              # Guardar base pointer
movq %rsp, %rbp         # Establecer nuevo frame
movl $9, -4(%rbp)       # a = 9
movl $11, -8(%rbp)      # b = 11
movl -4(%rbp), %edx     # EDX = a
movl -8(%rbp), %eax     # EAX = b
addl %edx, %eax         # EAX = EAX + EDX (resultado = 20)
movl %eax, -12(%rbp)    # guardar resultado
leave
ret
```

**Resultado esperado**: RAX = 20

---

### 8.2 Tabla Pipeline con Hazards

```
Código:
  I1: movl $10, %eax
  I2: addl %eax, %ebx   ← Depende de I1
  I3: movl %ebx, -4(%rbp)

Pipeline sin Forwarding:
┌───────┬─────┬─────┬─────┐
│ Ciclo │ I1  │ I2  │ I3  │
├───────┼─────┼─────┼─────┤
│   1   │ IF  │     │     │
│   2   │ ID  │ IF  │     │
│   3   │ EX  │ ID  │     │
│   4   │ MEM │STALL│ IF  │ ← Hazard
│   5   │ WB  │STALL│ ID  │
│   6   │     │ EX  │ ID  │
│   7   │     │ MEM │ EX  │
│   8   │     │ WB  │ MEM │
│   9   │     │     │ WB  │
└───────┴─────┴─────┴─────┘

Total: 9 ciclos (2 ciclos perdidos)
```

---

## 📚 Referencias

1. Bryant, R. E., & O'Hallaron, D. R. (2015). _Computer systems: A programmer's perspective_ (3rd ed.). Pearson.

2. Intel Corporation. (2023). _Intel® 64 and IA-32 architectures software developer's manual_. https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html

3. Patterson, D. A., & Hennessy, J. L. (2017). _Computer organization and design: RISC-V edition_. Morgan Kaufmann.

4. Stallings, W. (2015). _Computer organization and architecture_ (10th ed.). Pearson.

5. Tanenbaum, A. S., & Austin, T. (2013). _Structured computer organization_ (6th ed.). Pearson.

---

## 📋 Apéndices

### Apéndice A: Convenciones de Nomenclatura

**Rangos de Excel:**

- Prefijo `CELDA_`: Celdas individuales (ej. CELDA_PC)
- Prefijo `RANGO_`: Rangos múltiples (ej. RANGO_I_CACHE)
- Prefijo `Shape_`: Objetos gráficos (ej. Shape_Bus)

**Variables VBA:**

- Variables globales: PascalCase (ej. PC, Z1)
- Variables locales: camelCase (ej. direccionPC)
- Constantes: UPPER_SNAKE_CASE (ej. COLOR_ACTIVO)

---

### Apéndice B: Conjunto Completo de Instrucciones Soportadas

| Instrucción | Sintaxis          | Descripción              | Etapas                 |
| ----------- | ----------------- | ------------------------ | ---------------------- |
| MOV         | `movl src, dest`  | Transferencia de datos   | IF, ID, EX, WB         |
| ADD         | `addl src, dest`  | Suma                     | IF, ID, EX, WB         |
| SUB         | `subl src, dest`  | Resta                    | IF, ID, EX, WB         |
| MUL         | `mull src`        | Multiplicación sin signo | IF, ID, EX (3-4), WB   |
| DIV         | `divl src`        | División sin signo       | IF, ID, EX (20-40), WB |
| AND         | `andl src, dest`  | AND lógico               | IF, ID, EX, WB         |
| OR          | `orl src, dest`   | OR lógico                | IF, ID, EX, WB         |
| XOR         | `xorl src, dest`  | XOR lógico               | IF, ID, EX, WB         |
| CMP         | `cmpl src1, src2` | Comparación              | IF, ID, EX             |
| PUSH        | `pushq src`       | Apilar                   | IF, ID, EX, MEM        |
| POP         | `popq dest`       | Desapilar                | IF, ID, MEM, WB        |

---

## 📄 Licencia y Autores

### Licencia

**GPL v3** - Este proyecto es de código abierto bajo la licencia GNU General Public License v3.0.

### Autores

- **Alejandro Ramírez Vallejos** - [@alejandroramirezucb](https://github.com/alejandroramirezucb)
- **Josue Galo Balbontin Ugarteche** - [@josue-balbontin](https://github.com/josue-balbontin)
- **Fernando Terrazas Llanos** - [@FernandoTerrazasLl](https://github.com/FernandoTerrazasLl)

### Repositorio

📂 **GitHub:** [Simulador-de-Arquitectura-x86](https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86)

---

**¿Preguntas?** Abre un [issue](https://github.com/alejandroramirezucb/Simulador-de-Arquitectura-x86/issues) en GitHub.

**Contribuciones bienvenidas** mediante Pull Requests.
