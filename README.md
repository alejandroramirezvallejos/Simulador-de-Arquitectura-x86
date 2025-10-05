# Simulador de Arquitectura x86

[![Excel VBA](https://img.shields.io/badge/Excel_VBA-100%25-217346?logo=microsoftexcel)](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)
[![Architecture](https://img.shields.io/badge/Architecture-Von_Neumann-blue)](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-orange.svg)](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)
[![Status](https://img.shields.io/badge/Status-Complete-success)](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)

---

## 📋 Descripción General

Simulador interactivo de arquitectura x86 desarrollado en **Excel con VBA**. Esta herramienta permite visualizar y comprender el funcionamiento interno de un procesador moderno mediante la ejecución de código ensamblador en sintaxis AT&T, proporcionando una representación gráfica detallada del flujo de datos y control a través de un pipeline de cinco etapas.

El simulador implementa una **arquitectura Von Neumann**, donde instrucciones y datos comparten el mismo espacio de memoria, facilitando la comprensión de conceptos fundamentales de arquitectura de computadoras mediante visualización interactiva y simulación paso a paso.

---

## 📑 Tabla de Contenidos Completa

### **1. [Introducción](#-introducción)**

- 1.1 [Descripción General](#11-descripción-general)
- 1.2 [Objetivos del Proyecto](#12-objetivos-del-proyecto)
- 1.3 [Características Principales](#13-características-principales)

### **2. [Fundamentos Teóricos](#-fundamentos-teóricos)**

- 2.1 [Unidad de Control (Control Unit)](#21-unidad-de-control-control-unit)
  - 2.1.1 [Conceptualización](#211-conceptualización)
  - 2.1.2 [Componentes](#212-componentes)
  - 2.1.3 [Diseño en el Simulador](#213-diseño-en-el-simulador)
- 2.2 [Unidad Aritmético-Lógica (ALU)](#22-unidad-aritmético-lógica-alu)
  - 2.2.1 [Conceptualización](#221-conceptualización)
  - 2.2.2 [Operaciones Soportadas](#222-operaciones-soportadas)
  - 2.2.3 [Diseño en el Simulador](#223-diseño-en-el-simulador)
- 2.3 [Banco de Registros (Registers)](#23-banco-de-registros-registers)
  - 2.3.1 [Conceptualización](#231-conceptualización)
  - 2.3.2 [Jerarquía de Registros x86-64](#232-jerarquía-de-registros-x86-64)
  - 2.3.3 [Diseño en el Simulador](#233-diseño-en-el-simulador)
- 2.4 [Unidad de Memoria (Memory Unit)](#24-unidad-de-memoria-memory-unit)
  - 2.4.1 [Conceptualización](#241-conceptualización)
  - 2.4.2 [Principios de Localidad](#242-principios-de-localidad)
  - 2.4.3 [Diseño en el Simulador](#243-diseño-en-el-simulador)
- 2.5 [Memoria Virtual](#25-memoria-virtual)
  - 2.5.1 [Conceptualización](#251-conceptualización)
  - 2.5.2 [Tabla de Páginas](#252-tabla-de-páginas)
  - 2.5.3 [Diseño en el Simulador](#253-diseño-en-el-simulador)
- 2.6 [Memoria Caché](#26-memoria-caché)
  - 2.6.1 [Conceptualización](#261-conceptualización)
  - 2.6.2 [Jerarquía de Caché](#262-jerarquía-de-caché)
  - 2.6.3 [Política LRU](#263-política-lru)
  - 2.6.4 [Diseño en el Simulador](#264-diseño-en-el-simulador)
- 2.7 [Arquitectura Von Neumann](#27-arquitectura-von-neumann)
  - 2.7.1 [Conceptualización](#271-conceptualización)
  - 2.7.2 [Características Principales](#272-características-principales)
  - 2.7.3 [Ventajas y Desventajas](#273-ventajas-y-desventajas)
  - 2.7.4 [Implementación en el Simulador](#274-implementación-en-el-simulador)
- 2.8 [Ciclo de Instrucción](#28-ciclo-de-instrucción)
  - 2.8.1 [Conceptualización](#281-conceptualización)
  - 2.8.2 [Fases del Ciclo](#282-fases-del-ciclo)
  - 2.8.3 [Diseño en el Simulador](#283-diseño-en-el-simulador)
- 2.9 [Pipeline de Instrucciones](#29-pipeline-de-instrucciones)
  - 2.9.1 [Conceptualización](#291-conceptualización)
  - 2.9.2 [Beneficios del Pipeline](#292-beneficios-del-pipeline)
  - 2.9.3 [Estructura de 5 Etapas](#293-estructura-de-5-etapas)
  - 2.9.4 [Diseño en el Simulador](#294-diseño-en-el-simulador)

### **3. [Arquitectura del Simulador](#-arquitectura-del-simulador)**

- 3.1 [Visión de Alto Nivel](#31-visión-de-alto-nivel)
- 3.2 [Diagrama de Arquitectura](#32-diagrama-de-arquitectura)
- 3.3 [Componentes del Sistema](#33-componentes-del-sistema)
  - 3.3.1 [Capa de Presentación (Excel UI)](#331-capa-de-presentación-excel-ui)
  - 3.3.2 [Capa de Control (VBA)](#332-capa-de-control-vba)
  - 3.3.3 [Capa de Datos](#333-capa-de-datos)
- 3.4 [Flujo de Datos End-to-End](#34-flujo-de-datos-end-to-end)

### **4. [Decisiones de Diseño](#-decisiones-de-diseño)**

- 4.1 [Elección de Plataforma: Excel + VBA](#41-elección-de-plataforma-excel--vba)
- 4.2 [Arquitectura Von Neumann](#42-arquitectura-von-neumann)
- 4.3 [Pipeline de 5 Etapas](#43-pipeline-de-5-etapas)
- 4.4 [Gestión Dinámica de Registros](#44-gestión-dinámica-de-registros)
- 4.5 [Simulación de Memoria con Dictionary](#45-simulación-de-memoria-con-dictionary)
- 4.6 [Política de Caché LRU](#46-política-de-caché-lru)
- 4.7 [Sintaxis AT&T](#47-sintaxis-att)
- 4.8 [Visualización en Tiempo Real](#48-visualización-en-tiempo-real)

### **5. [Componentes Implementados](#-componentes-implementados)**

- 5.1 [Listado de Módulos VBA](#51-listado-de-módulos-vba)
- 5.2 [Módulo 1: Pipeline Visual](#52-módulo-1-pipeline-visual)
- 5.3 [Módulo 2: Motor de Simulación](#53-módulo-2-motor-de-simulación)
- 5.4 [Módulo 3: Sistema de Registros](#54-módulo-3-sistema-de-registros)
- 5.5 [Módulo 4: ALU](#55-módulo-4-alu)
- 5.6 [Módulo 5: Gestión de Memoria](#56-módulo-5-gestión-de-memoria)
- 5.7 [Módulo 6: Sistema de Caché](#57-módulo-6-sistema-de-caché)
- 5.8 [Módulo 7: Unidad de Control](#58-módulo-7-unidad-de-control)
- 5.9 [Módulo 8: Parser AT&T](#59-módulo-8-parser-att)
- 5.10 [Módulo 9: Utilidades](#510-módulo-9-utilidades)

### **6. [Manejo de Hazards y Dependencias](#-manejo-de-hazards-y-dependencias)**

- 6.1 [Tipos de Hazards](#61-tipos-de-hazards)
  - 6.1.1 [Hazards de Datos (RAW, WAW, WAR)](#611-hazards-de-datos-raw-waw-war)
  - 6.1.2 [Hazards Estructurales](#612-hazards-estructurales)
  - 6.1.3 [Hazards de Control](#613-hazards-de-control)
- 6.2 [Políticas de Mitigación](#62-políticas-de-mitigación)
  - 6.2.1 [Stalling (Inserción de Burbujas)](#621-stalling-inserción-de-burbujas)
  - 6.2.2 [Forwarding/Bypassing](#622-forwardingbypassing)
  - 6.2.3 [Reordenamiento de Código](#623-reordenamiento-de-código)
- 6.3 [Visualización de Hazards](#63-visualización-de-hazards)
- 6.4 [Comparación de Rendimiento](#64-comparación-de-rendimiento)

### **7. [Guía de Uso Detallada](#-guía-de-uso-detallada)**

- 7.1 [Requisitos del Sistema](#71-requisitos-del-sistema)
- 7.2 [Instalación](#72-instalación)
  - 7.2.1 [Descargar el Repositorio](#721-descargar-el-repositorio)
  - 7.2.2 [Configurar Excel](#722-configurar-excel)
  - 7.2.3 [Habilitar Macros](#723-habilitar-macros)
  - 7.2.4 [Verificar Instalación](#724-verificar-instalación)
- 7.3 [Configuración Inicial](#73-configuración-inicial)
  - 7.3.1 [Estructura de Hojas](#731-estructura-de-hojas)
  - 7.3.2 [Rangos Nombrados](#732-rangos-nombrados)
  - 7.3.3 [Configuración de Colores](#733-configuración-de-colores)
- 7.4 [Uso Básico](#74-uso-básico)
  - 7.4.1 [Cargar Código Ensamblador](#741-cargar-código-ensamblador)
  - 7.4.2 [Ejecutar Paso a Paso](#742-ejecutar-paso-a-paso)
  - 7.4.3 [Simular Pipeline Completo](#743-simular-pipeline-completo)
  - 7.4.4 [Visualizar Memoria](#744-visualizar-memoria)
  - 7.4.5 [Inspeccionar Registros](#745-inspeccionar-registros)
- 7.5 [Funciones Avanzadas](#75-funciones-avanzadas)
  - 7.5.1 [Modo Debugging](#751-modo-debugging)
  - 7.5.2 [Análisis de Rendimiento](#752-análisis-de-rendimiento)
  - 7.5.3 [Exportar Resultados](#753-exportar-resultados)
  - 7.5.4 [Configurar Velocidad de Simulación](#754-configurar-velocidad-de-simulación)
- 7.6 [Solución de Problemas](#76-solución-de-problemas)
  - 7.6.1 [Errores Comunes](#761-errores-comunes)
  - 7.6.2 [Resetear Simulador](#762-resetear-simulador)
  - 7.6.3 [Diagnóstico de Problemas](#763-diagnóstico-de-problemas)

### **8. [Ejemplos Prácticos](#-ejemplos-prácticos)**

- 8.1 [Ejemplo 1: Programa Simple](#81-ejemplo-1-programa-simple)
  - 8.1.1 [Código Fuente](#811-código-fuente)
  - 8.1.2 [Análisis de Instrucciones](#812-análisis-de-instrucciones)
  - 8.1.3 [Ejecución Paso a Paso](#813-ejecución-paso-a-paso)
- 8.2 [Ejemplo 2: Análisis de Pipeline](#82-ejemplo-2-análisis-de-pipeline)
  - 8.2.1 [Tabla Ciclo-a-Ciclo Sin Forwarding](#821-tabla-ciclo-a-ciclo-sin-forwarding)
  - 8.2.2 [Tabla Ciclo-a-Ciclo Con Forwarding](#822-tabla-ciclo-a-ciclo-con-forwarding)
  - 8.2.3 [Comparación de Rendimiento](#823-comparación-de-rendimiento)
- 8.3 [Ejemplo 3: Gestión de Memoria](#83-ejemplo-3-gestión-de-memoria)
  - 8.3.1 [Operaciones PUSH/POP](#831-operaciones-pushpop)
  - 8.3.2 [Acceso a Stack](#832-acceso-a-stack)
  - 8.3.3 [Visualización de Memoria](#833-visualización-de-memoria)
- 8.4 [Ejemplo 4: Casos de Uso Avanzados](#84-ejemplo-4-casos-de-uso-avanzados)
  - 8.4.1 [Bucles](#841-bucles)
  - 8.4.2 [Funciones con Parámetros](#842-funciones-con-parámetros)
  - 8.4.3 [Estructuras de Datos](#843-estructuras-de-datos)

### **9. [Desarrollo del Proyecto](#-desarrollo-del-proyecto)**

- 9.1 [Roadmap Cronológico](#91-roadmap-cronológico)
- 9.2 [Distribución de Trabajo](#92-distribución-de-trabajo)
- 9.3 [Métricas del Proyecto](#93-métricas-del-proyecto)
- 9.4 [Historias de Usuario](#94-historias-de-usuario)

### **10. [Contribuciones](#-contribuciones)**

- 10.1 [Cómo Contribuir](#101-cómo-contribuir)
- 10.2 [Guía de Estilo de Código](#102-guía-de-estilo-de-código)
- 10.3 [Reporte de Bugs](#103-reporte-de-bugs)
- 10.4 [Propuesta de Nuevas Características](#104-propuesta-de-nuevas-características)

### **11. [Referencias y Recursos](#-referencias-y-recursos)**

- 11.1 [Literatura Académica](#111-literatura-académica)
- 11.2 [Recursos en Línea](#112-recursos-en-línea)
- 11.3 [Documentación Adicional](#113-documentación-adicional)

### **12. [Licencia y Autores](#-licencia-y-autores)**

- 12.1 [Licencia](#121-licencia)
- 12.2 [Autores](#122-autores)
- 12.3 [Agradecimientos](#123-agradecimientos)

---

## 🎯 Introducción

### 1.1 Descripción General

El Simulador de Arquitectura x86 es una herramienta desarrollada completamente en **Microsoft Excel con Visual Basic for Applications (VBA)**. Su objetivo principal es proporcionar una plataforma visual e interactiva para el aprendizaje de conceptos fundamentales de arquitectura de computadoras, específicamente la arquitectura x86-64.

El simulador permite ejecutar código ensamblador en sintaxis AT&T, visualizando en tiempo real el comportamiento del procesador a través de sus componentes principales: unidad de control, ALU, registros, memoria, y pipeline de instrucciones.

### 1.2 Objetivos del Proyecto

1. **Educación Visual**: Proporcionar una representación gráfica del funcionamiento interno de un procesador
2. **Comprensión del Pipeline**: Facilitar el entendimiento de la ejecución superpuesta de instrucciones
3. **Análisis de Hazards**: Mostrar las dependencias entre instrucciones y sus soluciones
4. **Gestión de Memoria**: Ilustrar la jerarquía de memoria (registros, caché, RAM, memoria virtual)
5. **Accesibilidad**: Utilizar una plataforma familiar (Excel) para reducir la curva de aprendizaje

### 1.3 Características Principales

| Característica           | Descripción                                                              |
| ------------------------ | ------------------------------------------------------------------------ |
| **Arquitectura**         | Von Neumann (memoria unificada para instrucciones y datos)               |
| **Plataforma**           | Microsoft Excel con macros VBA                                           |
| **Sintaxis Soportada**   | AT&T Assembly (x86-64)                                                   |
| **Pipeline**             | 5 etapas (IF, ID, EX, MEM, WB)                                           |
| **Registros**            | 16 registros de propósito general (RAX-R15) con normalización automática |
| **Memoria**              | Jerarquía completa: L1 I-Cache, L1 D-Cache, L2, L3, RAM, Memoria Virtual |
| **Instrucciones**        | MOV, ADD, SUB, MUL, DIV, PUSH, POP, CMP, JMP y más                       |
| **Detección de Hazards** | RAW, WAW, WAR con inserción automática de stalls                         |
| **Forwarding**           | Rutas de bypass EX→EX, MEM→EX, WB→EX (visualización)                     |
| **Visualización**        | Colores dinámicos, resaltado de componentes activos, animaciones         |
| **Flags**                | ZF, SF, CF, OF actualizados automáticamente                              |
| **Debugging**            | Ejecución paso a paso con inspección de estado                           |

---

## 📚 Fundamentos Teóricos

### 2.1 Unidad de Control (Control Unit)

#### 2.1.1 Conceptualización

La Unidad de Control (UC) es el componente orquestador del procesador. Actúa como el "cerebro" del sistema, coordinando todas las operaciones mediante la generación de señales de control que activan y desactivan los diferentes componentes en el momento adecuado.

**Responsabilidades principales:**

1. **Secuenciación**: Mantener el orden correcto de ejecución de instrucciones
2. **Temporización**: Generar señales de reloj y controlar el timing de operaciones
3. **Decodificación**: Interpretar instrucciones y generar microoperaciones
4. **Coordinación**: Sincronizar el trabajo de ALU, memoria y registros

#### 2.1.2 Componentes

```
┌─────────────────────────────────────────────┐
│         UNIDAD DE CONTROL                   │
├─────────────────────────────────────────────┤
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Program Counter (PC)                │  │
│  │  • Apunta a la siguiente instrucción │  │
│  │  • Se incrementa automáticamente     │  │
│  │  • Tamaño: 64 bits                   │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Instruction Register (IR)           │  │
│  │  • Almacena instrucción actual       │  │
│  │  • Entrada para el decodificador     │  │
│  │  • Tamaño: variable                  │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Memory Address Register (MAR)       │  │
│  │  • Dirección a acceder en memoria    │  │
│  │  • Conectado al bus de direcciones   │  │
│  │  • Tamaño: 64 bits                   │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Memory Data Register (MDR)          │  │
│  │  • Dato a leer/escribir              │  │
│  │  • Buffer entre CPU y memoria        │  │
│  │  • Tamaño: 64 bits                   │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Decodificador de Instrucciones      │  │
│  │  • Extrae opcode y operandos         │  │
│  │  • Genera señales de control         │  │
│  └──────────────────────────────────────┘  │
│                                             │
└─────────────────────────────────────────────┘
```

#### 2.1.3 Diseño en el Simulador

**Representación Visual:**

- **PC**: Celda `CELDA_PC` muestra la dirección actual en formato hexadecimal
- **IR**: Shape `R.I` contiene la instrucción en ejecución
- **MAR**: Celda `CELDA_MAR` durante accesos a memoria
- **MDR**: Celda `CELDA_MDR` durante transferencias

**Implementación VBA:**

```vba
' Variable global para Program Counter
Public PC As Long

Sub InicializarUnidadControl()
    ' Inicializar PC en la primera instrucción
    PC = 0
    CELDA_PC.Value = "0x" & Hex(PC)
    CELDA_IR.Value = ""
    CELDA_MAR.Value = ""
    CELDA_MDR.Value = ""
End Sub

Sub IncrementarPC()
    ' Avanzar a la siguiente instrucción
    PC = PC + 1
    CELDA_PC.Value = "0x" & Hex(PC)

    ' Resaltar visualmente el cambio
    Call ResaltarTemporal(CELDA_PC, COLOR_ACTIVO, 0.5)
End Sub
```

**Flujo de Control:**

```
     ┌─────────┐
     │ INICIO  │
     └────┬────┘
          │
          ▼
     ┌─────────┐
     │ Leer PC │
     └────┬────┘
          │
          ▼
     ┌──────────────┐
     │ Fetch        │
     │ Instrucción  │
     └────┬─────────┘
          │
          ▼
     ┌──────────────┐
     │ Cargar en IR │
     └────┬─────────┘
          │
          ▼
     ┌──────────────┐
     │ Incrementar  │
     │ PC           │
     └────┬─────────┘
          │
          ▼
     ┌──────────────┐
     │ Decode       │
     └────┬─────────┘
          │
          ▼
     ┌──────────────┐
     │ Execute      │
     └────┬─────────┘
          │
          ▼
     ┌──────────────┐
     │ ¿Más instr.? │
     └─┬──────────┬─┘
    Sí │          │ No
       │          ▼
       │     ┌─────────┐
       └────►│   FIN   │
             └─────────┘
```

---

### 2.2 Unidad Aritmético-Lógica (ALU)

#### 2.2.1 Conceptualización

La ALU (Arithmetic Logic Unit) es el núcleo computacional del procesador. Realiza todas las operaciones aritméticas y lógicas sobre datos binarios, generando resultados y actualizando flags de estado.

**Características fundamentales:**

1. **Operaciones Aritméticas**: Suma, resta, multiplicación, división
2. **Operaciones Lógicas**: AND, OR, XOR, NOT, desplazamientos
3. **Comparaciones**: CMP (resta sin almacenar resultado)
4. **Actualización de Flags**: ZF, SF, CF, OF según el resultado

#### 2.2.2 Operaciones Soportadas

**Tabla Completa de Instrucciones:**

| Instrucción | Sintaxis          | Operación                    | Flags Afectados     | Ciclos | Ejemplo            |
| ----------- | ----------------- | ---------------------------- | ------------------- | ------ | ------------------ |
| **MOV**     | `movl src, dest`  | dest = src                   | Ninguno             | 1      | `movl $10, %eax`   |
| **ADD**     | `addl src, dest`  | dest = dest + src            | ZF, SF, CF, OF      | 1      | `addl %ebx, %eax`  |
| **SUB**     | `subl src, dest`  | dest = dest - src            | ZF, SF, CF, OF      | 1      | `subl $5, %eax`    |
| **MUL**     | `mull src`        | RDX:RAX = RAX × src          | CF, OF              | 3-4    | `mull %ebx`        |
| **IMUL**    | `imull src, dest` | dest = dest × src            | CF, OF              | 3-4    | `imull $3, %eax`   |
| **DIV**     | `divl src`        | RAX = RDX:RAX / src          | Indefinido          | 20-40  | `divl %ebx`        |
| **IDIV**    | `idivl src`       | RAX = RDX:RAX / src (signed) | Indefinido          | 20-40  | `idivl %ecx`       |
| **AND**     | `andl src, dest`  | dest = dest & src            | ZF, SF (CF=0, OF=0) | 1      | `andl $0xFF, %eax` |
| **OR**      | `orl src, dest`   | dest = dest \| src           | ZF, SF (CF=0, OF=0) | 1      | `orl %ebx, %eax`   |
| **XOR**     | `xorl src, dest`  | dest = dest ^ src            | ZF, SF (CF=0, OF=0) | 1      | `xorl %eax, %eax`  |
| **NOT**     | `notl dest`       | dest = ~dest                 | Ninguno             | 1      | `notl %eax`        |
| **CMP**     | `cmpl src1, src2` | temp = src2 - src1           | ZF, SF, CF, OF      | 1      | `cmpl $0, %eax`    |
| **PUSH**    | `pushq src`       | RSP-=8; [RSP]=src            | Ninguno             | 2      | `pushq %rax`       |
| **POP**     | `popq dest`       | dest=[RSP]; RSP+=8           | Ninguno             | 2      | `popq %rax`        |

**Descripción de Flags:**

- **ZF (Zero Flag)**: Se activa (=1) si el resultado es cero
- **SF (Sign Flag)**: Se activa (=1) si el resultado es negativo (bit más significativo = 1)
- **CF (Carry Flag)**: Se activa (=1) en overflow aritmético sin signo
- **OF (Overflow Flag)**: Se activa (=1) en overflow aritmético con signo

#### 2.2.3 Diseño en el Simulador

**Arquitectura de la ALU:**

```
┌─────────────────────────────────────────────────┐
│                    ALU                          │
├─────────────────────────────────────────────────┤
│                                                 │
│  Entradas:                                      │
│  ┌──────────────┐        ┌──────────────┐      │
│  │   Input 1    │        │   Input 2    │      │
│  │ (Operando A) │        │ (Operando B) │      │
│  └──────┬───────┘        └──────┬───────┘      │
│         │                       │              │
│         └───────────┬───────────┘              │
│                     │                          │
│            ┌────────▼─────────┐                │
│            │   Selector de    │                │
│            │    Operación     │                │
│            └────────┬─────────┘                │
│                     │                          │
│     ┌───────────────┼───────────────┐          │
│     │               │               │          │
│ ┌───▼────┐     ┌───▼────┐     ┌───▼────┐      │
│ │Aritmética│   │ Lógica │     │Desplaz.│      │
│ │  Unit    │   │  Unit  │     │  Unit  │      │
│ └───┬────┘     └───┬────┘     └───┬────┘      │
│     └───────────────┼───────────────┘          │
│                     │                          │
│            ┌────────▼─────────┐                │
│            │   Multiplexor    │                │
│            └────────┬─────────┘                │
│                     │                          │
│  Salidas:           │                          │
│  ┌──────────────────▼───────┐                  │
│  │    Resultado (Z1)        │                  │
│  │  RANGE_ALU_OUTPUT        │                  │
│  └──────────────────────────┘                  │
│                                                 │
│  ┌─────────────────────────────────────┐       │
│  │  Registro de Flags                  │       │
│  │  ┌────┬────┬────┬────┐              │       │
│  │  │ ZF │ SF │ CF │ OF │              │       │
│  │  └────┴────┴────┴────┘              │       │
│  └─────────────────────────────────────┘       │
│                                                 │
└─────────────────────────────────────────────────┘
```

**Implementación VBA:**

```vba
' Registros temporales de resultado
Public Z1 As Long  ' Resultado principal
Public Z2 As Long  ' Resultado secundario (para MUL/DIV)

' Flags del procesador
Public ZF As Integer  ' Zero Flag
Public SF As Integer  ' Sign Flag
Public CF As Integer  ' Carry Flag
Public OF As Integer  ' Overflow Flag

Sub EjecutarEnALU(instruccion As String)
    ' ================================================
    ' EJECUCIÓN DE INSTRUCCIÓN EN LA ALU
    ' ================================================

    Dim opcode As String, operando1 As String, operando2 As String
    Dim tipoOp1 As String, tipoOp2 As String
    Dim valorOp1 As Long, valorOp2 As Long
    Dim resultado As Long

    ' Paso 1: Parsear la instrucción
    Call ParsearInstruccionDirecta(instruccion, opcode, operando1, operando2)

    ' Paso 2: Visualizar operandos en celdas de entrada
    RANGE_ALU_INPUT1.Value = operando1
    RANGE_ALU_INPUT2.Value = operando2
    Call ResaltarTemporal(RANGE_ALU_INPUT1, COLOR_ALU_INPUT, 0.3)
    Call ResaltarTemporal(RANGE_ALU_INPUT2, COLOR_ALU_INPUT, 0.3)

    ' Paso 3: Obtener valores de los operandos
    Call ParsearOperando(operando1, tipoOp1, valorOp1)
    Call ParsearOperando(operando2, tipoOp2, valorOp2)

    valorOp1 = ObtenerValorOperando(tipoOp1, valorOp1)
    valorOp2 = ObtenerValorOperando(tipoOp2, valorOp2)

    ' Paso 4: Actualizar estado visual de la ALU
    EstadoALU_Shape.TextFrame.Characters.Text = "Ejecutando: " & UCase(opcode)
    EstadoALU_Shape.Fill.ForeColor.RGB = COLOR_ACTIVO

    ' Paso 5: Ejecutar operación según opcode
    Select Case UCase(opcode)
        ' -------- TRANSFERENCIA --------
        Case "MOV", "MOVL", "MOVQ"
            resultado = valorOp2
            ' MOV no afecta flags

        ' -------- ARITMÉTICAS --------
        Case "ADD", "ADDL"
            resultado = valorOp1 + valorOp2
            Call ActualizarFlags(resultado)

        Case "SUB", "SUBL"
            resultado = valorOp1 - valorOp2
            Call ActualizarFlags(resultado)

        Case "MUL", "MULL"
            resultado = valorOp1 * valorOp2
            CF = IIf(Abs(resultado) > &H7FFFFFFF, 1, 0)
            OF = CF

        Case "IMUL", "IMULL"
            resultado = valorOp1 * valorOp2
            CF = IIf(Abs(resultado) > &H7FFFFFFF, 1, 0)
            OF = CF

        Case "DIV", "DIVL"
            If valorOp2 <> 0 Then
                resultado = valorOp1 \ valorOp2  ' División entera
                Z2 = valorOp1 Mod valorOp2       ' Resto en Z2
            Else
                MsgBox "Error: División por cero", vbCritical
                Exit Sub
            End If

        Case "IDIV", "IDIVL"
            If valorOp2 <> 0 Then
                resultado = valorOp1 \ valorOp2
                Z2 = valorOp1 Mod valorOp2
            Else
                MsgBox "Error: División por cero", vbCritical
                Exit Sub
            End If

        ' -------- LÓGICAS --------
        Case "AND", "ANDL"
            resultado = valorOp1 And valorOp2
            Call ActualizarFlags(resultado)
            CF = 0
            OF = 0

        Case "OR", "ORL"
            resultado = valorOp1 Or valorOp2
            Call ActualizarFlags(resultado)
            CF = 0
            OF = 0

        Case "XOR", "XORL"
            resultado = valorOp1 Xor valorOp2
            Call ActualizarFlags(resultado)
            CF = 0
            OF = 0

        Case "NOT", "NOTL"
            resultado = Not valorOp1
            ' NOT no afecta flags

        ' -------- COMPARACIÓN --------
        Case "CMP", "CMPL"
            resultado = valorOp1 - valorOp2
            Call ActualizarFlags(resultado)
            ' CMP no escribe resultado, solo actualiza flags
            Exit Sub

        ' -------- STACK --------
        Case "PUSH", "PUSHQ"
            ' Decrementar RSP
            Dim rsp As Long
            rsp = LeerRegistro("RSP")
            rsp = rsp - 8
            Call EscribirRegistro("RSP", rsp)

            ' Escribir valor en memoria
            Call EscribirMemoria("(%rsp)", valorOp1)
            Exit Sub

        Case "POP", "POPQ"
            ' Leer valor de memoria
            rsp = LeerRegistro("RSP")
            resultado = LeerMemoria("(%rsp)")

            ' Incrementar RSP
            rsp = rsp + 8
            Call EscribirRegistro("RSP", rsp)

        Case Else
            MsgBox "Instrucción no soportada: " & opcode, vbExclamation
            Exit Sub
    End Select

    ' Paso 6: Escribir resultado en Z1
    Z1 = resultado
    RANGE_ALU_OUTPUT.Value = "0x" & Hex(resultado) & " (" & resultado & ")"
    Call ResaltarTemporal(RANGE_ALU_OUTPUT, COLOR_ALU_OUTPUT, 0.5)

    ' Paso 7: Actualizar visualización de flags
    Call VisualizarFlags
End Sub

Sub ActualizarFlags(valor As Long)
    ' ================================================
    ' ACTUALIZACIÓN DE FLAGS DEL PROCESADOR
    ' ================================================

    ' Zero Flag: Se activa si el resultado es 0
    If valor = 0 Then
        ZF = 1
    Else
        ZF = 0
    End If

    ' Sign Flag: Se activa si el resultado es negativo
    If valor < 0 Then
        SF = 1
    Else
        SF = 0
    End If

    ' Carry Flag: Simplificado (overflow sin signo)
    If valor > &H7FFFFFFF Or valor < &H80000000 Then
        CF = 1
    Else
        CF = 0
    End If

    ' Overflow Flag: Simplificado (overflow con signo)
    ' En implementación real requiere análisis de bits de signo
    OF = 0
End Sub

Sub VisualizarFlags()
    ' Actualizar shape de flags
    Dim textoFlags As String
    textoFlags = "ZF=" & ZF & " SF=" & SF & " CF=" & CF & " OF=" & OF

    Flags_Shape.TextFrame.Characters.Text = textoFlags

    ' Colorear según estado
    If ZF = 1 Then
        Flags_Shape.Fill.ForeColor.RGB = COLOR_FLAG_ACTIVO
    Else
        Flags_Shape.Fill.ForeColor.RGB = COLOR_FLAG_INACTIVO
    End If
End Sub
```

---

### 2.3 Banco de Registros (Registers)

#### 2.3.1 Conceptualización

Los registros son la memoria más rápida del procesador, ubicados dentro del chip de la CPU. En arquitectura x86-64, constituyen el nivel más alto de la jerarquía de memoria.

**Características:**

- **Velocidad**: Acceso en < 1 ciclo de reloj
- **Tamaño**: 64 bits en x86-64 (compatibles con 32, 16, 8 bits)
- **Cantidad**: 16 registros de propósito general + registros especiales
- **Acceso**: Lectura/escritura simultánea en múltiples registros

#### 2.3.2 Jerarquía de Registros x86-64

**Mapa Completo de Registros:**

```
┌───────────────────────────────────────────────────────────────────┐
│              REGISTROS DE PROPÓSITO GENERAL x86-64                │
├────────────┬──────────┬──────────┬──────────────┬─────────────────┤
│  64-bit    │  32-bit  │  16-bit  │    8-bit     │   Uso Típico    │
├────────────┼──────────┼──────────┼──────────────┼─────────────────┤
│  RAX       │  EAX     │  AX      │  AH    AL    │  Acumulador     │
│  RBX       │  EBX     │  BX      │  BH    BL    │  Base           │
│  RCX       │  ECX     │  CX      │  CH    CL    │  Contador       │
│  RDX       │  EDX     │  DX      │  DH    DL    │  Datos          │
│  RSI       │  ESI     │  SI      │         SIL  │  Source Index   │
│  RDI       │  EDI     │  DI      │         DIL  │  Dest. Index    │
│  RBP       │  EBP     │  BP      │         BPL  │  Base Pointer   │
│  RSP       │  ESP     │  SP      │         SPL  │  Stack Pointer  │
│  R8        │  R8D     │  R8W     │         R8B  │  General        │
│  R9        │  R9D     │  R9W     │         R9B  │  General        │
│  R10       │  R10D    │  R10W    │         R10B │  General        │
│  R11       │  R11D    │  R11W    │         R11B │  General        │
│  R12       │  R12D    │  R12W    │         R12B │  General        │
│  R13       │  R13D    │  R13W    │         R13B │  General        │
│  R14       │  R14D    │  R14W    │         R14B │  General        │
│  R15       │  R15D    │  R15W    │         R15B │  General        │
└────────────┴──────────┴──────────┴──────────────┴─────────────────┘

┌───────────────────────────────────────────────────────────────────┐
│                  REGISTROS ESPECIALES                             │
├────────────┬──────────────────────────────────────────────────────┤
│  RIP       │  Instruction Pointer (Program Counter)              │
│  RFLAGS    │  Registro de Flags (ZF, SF, CF, OF, etc.)           │
│  CS        │  Code Segment                                       │
│  DS        │  Data Segment                                       │
│  SS        │  Stack Segment                                      │
│  ES        │  Extra Segment                                      │
│  FS        │  Extra Segment 2                                    │
│  GS        │  Extra Segment 3                                    │
└────────────┴──────────────────────────────────────────────────────┘
```

**Ejemplo de Acceso a Diferentes Tamaños:**

```assembly
; Acceso a 64 bits (RAX completo)
movq $0x123456789ABCDEF0, %rax

; Acceso a 32 bits inferiores (EAX)
movl $0x12345678, %eax     ; RAX = 0x0000000012345678

; Acceso a 16 bits inferiores (AX)
movw $0x1234, %ax          ; RAX = 0x0000000000001234

; Acceso a 8 bits bajos (AL)
movb $0x12, %al            ; RAX = 0x0000000000000012

; Acceso a 8 bits altos (AH)
movb $0x34, %ah            ; RAX = 0x0000000000003412
```

#### 2.3.3 Diseño en el Simulador

**Sistema de Normalización:**

Todas las operaciones se normalizan internamente a registros de 64 bits para simplificar la gestión.

```vba
Function NormalizarNombreRegistro(regRaw As String) As String
    ' ================================================
    ' NORMALIZACIÓN DE NOMBRES DE REGISTRO
    ' ================================================
    ' Convierte cualquier variante del nombre de un registro
    ' a su versión de 64 bits (RAX, RBX, etc.)

    Dim reg As String
    reg = UCase(Trim(Replace(regRaw, "%", "")))  ' Eliminar % y convertir a mayúsculas

    ' -------- REGISTROS DE 32 BITS --------
    Select Case reg
        Case "EAX": NormalizarNombreRegistro = "RAX"
        Case "EBX": NormalizarNombreRegistro = "RBX"
        Case "ECX": NormalizarNombreRegistro = "RCX"
        Case "EDX": NormalizarNombreRegistro = "RDX"
        Case "ESI": NormalizarNombreRegistro = "RSI"
        Case "EDI": NormalizarNombreRegistro = "RDI"
        Case "EBP": NormalizarNombreRegistro = "RBP"
        Case "ESP": NormalizarNombreRegistro = "RSP"

    ' -------- REGISTROS DE 16 BITS --------
        Case "AX": NormalizarNombreRegistro = "RAX"
        Case "BX": NormalizarNombreRegistro = "RBX"
        Case "CX": NormalizarNombreRegistro = "RCX"
        Case "DX": NormalizarNombreRegistro = "RDX"
        Case "SI": NormalizarNombreRegistro = "RSI"
        Case "DI": NormalizarNombreRegistro = "RDI"
        Case "BP": NormalizarNombreRegistro = "RBP"
        Case "SP": NormalizarNombreRegistro = "RSP"

    ' -------- REGISTROS DE 8 BITS --------
        Case "AL", "AH": NormalizarNombreRegistro = "RAX"
        Case "BL", "BH": NormalizarNombreRegistro = "RBX"
        Case "CL", "CH": NormalizarNombreRegistro = "RCX"
        Case "DL", "DH": NormalizarNombreRegistro = "RDX"
        Case "SIL": NormalizarNombreRegistro = "RSI"
        Case "DIL": NormalizarNombreRegistro = "RDI"
        Case "BPL": NormalizarNombreRegistro = "RBP"
        Case "SPL": NormalizarNombreRegistro = "RSP"

    ' -------- REGISTROS R8-R15 --------
        Case "R8D", "R8W", "R8B": NormalizarNombreRegistro = "R8"
        Case "R9D", "R9W", "R9B": NormalizarNombreRegistro = "R9"
        Case "R10D", "R10W", "R10B": NormalizarNombreRegistro = "R10"
        Case "R11D", "R11W", "R11B": NormalizarNombreRegistro = "R11"
        Case "R12D", "R12W", "R12B": NormalizarNombreRegistro = "R12"
        Case "R13D", "R13W", "R13B": NormalizarNombreRegistro = "R13"
        Case "R14D", "R14W", "R14B": NormalizarNombreRegistro = "R14"
        Case "R15D", "R15W", "R15B": NormalizarNombreRegistro = "R15"

    ' -------- YA ESTÁ EN FORMATO DE 64 BITS --------
        Case Else
            NormalizarNombreRegistro = reg
    End Select
End Function
```

**Gestión Dinámica de Registros:**

```vba
' Diccionario global para almacenar registros
Public registrosDict As Object  ' Scripting.Dictionary

Sub InicializarSistemaRegistros()
    ' ================================================
    ' INICIALIZACIÓN DEL SISTEMA DE REGISTROS
    ' ================================================

    ' Crear diccionario si no existe
    If registrosDict Is Nothing Then
        Set registrosDict = CreateObject("Scripting.Dictionary")
    End If
    registrosDict.RemoveAll

    ' -------- REGISTROS BÁSICOS --------
    Dim registrosBase As Variant
    registrosBase = Array("RAX", "RBX", "RCX", "RDX", _
                          "RSI", "RDI", "RBP", "RSP", _
                          "R8", "R9", "R10", "R11", _
                          "R12", "R13", "R14", "R15")

    Dim i As Integer
    For i = LBound(registrosBase) To UBound(registrosBase)
        registrosDict.Add registrosBase(i), 0&  ' Inicializar en 0
    Next i

    ' -------- VALORES INICIALES ESPECIALES --------
    ' Stack Pointer: Dirección alta de memoria
    registrosDict("RSP") = &H7FFFFFFFE000
    ' Base Pointer: Igual al Stack Pointer inicialmente
    registrosDict("RBP") = &H7FFFFFFFE000

    ' -------- ESCANEAR CÓDIGO PARA DETECTAR REGISTROS USADOS --------
    Call DetectarRegistrosEnCodigo

    ' -------- RENDERIZAR EN EXCEL --------
    Call RenderizarRegistrosEnExcel
End Sub

Sub DetectarRegistrosEnCodigo()
    ' ================================================
    ' DETECCIÓN AUTOMÁTICA DE REGISTROS EN EL CÓDIGO
    ' ================================================

    Dim ws As Worksheet
    Set ws = ThisWorkbook.Worksheets("Hoja2")  ' Hoja con código

    Dim fila As Long
    fila = 3  ' Fila inicial del código

    Do While ws.Cells(fila, 1).Value <> ""
        Dim instruccion As String
        instruccion = Trim(ws.Cells(fila, 1).Value)

        ' Extraer registros de la instrucción
        Dim regs As Collection
        Set regs = ExtraerRegistrosDeInstruccion(instruccion)

        ' Añadir registros al diccionario si no existen
        Dim reg As Variant
        For Each reg In regs
            Dim regNorm As String
            regNorm = NormalizarNombreRegistro(CStr(reg))

            If Not registrosDict.Exists(regNorm) Then
                registrosDict.Add regNorm, 0&
            End If
        Next reg

        fila = fila + 1
    Loop
End Sub

Function ExtraerRegistrosDeInstruccion(instruccion As String) As Collection
    ' ================================================
    ' EXTRACCIÓN DE REGISTROS DE UNA INSTRUCCIÓN
    ' ================================================

    Set ExtraerRegistrosDeInstruccion = New Collection

    ' Buscar patrones %reg
    Dim regex As Object
    Set regex = CreateObject("VBScript.RegExp")
    regex.Global = True
    regex.Pattern = "%[a-zA-Z0-9]+"

    Dim matches As Object
    Set matches = regex.Execute(instruccion)

    Dim match As Variant
    For Each match In matches
        On Error Resume Next
        ExtraerRegistrosDeInstruccion.Add match.Value, match.Value
        On Error GoTo 0
    Next match
End Function

Sub RenderizarRegistrosEnExcel()
    ' ================================================
    ' RENDERIZACIÓN VISUAL DE REGISTROS EN EXCEL
    ' ================================================

    Dim ws As Worksheet
    Set ws = ThisWorkbook.Worksheets("Hoja2")

    ' Rango de visualización
    Dim rangoInicio As Range
    Set rangoInicio = ws.Range("F3")

    ' Encabezados
    rangoInicio.Offset(0, 0).Value = "Registro"
    rangoInicio.Offset(0, 1).Value = "Valor (Hex)"
    rangoInicio.Offset(0, 2).Value = "Valor (Dec)"

    ' Formato de encabezados
    With rangoInicio.Resize(1, 3)
        .Font.Bold = True
        .Interior.Color = RGB(200, 200, 200)
        .Borders.LineStyle = xlContinuous
    End With

    ' Datos
    Dim fila As Long
    fila = 1

    Dim clave As Variant
    For Each clave In registrosDict.Keys
        Dim valorReg As Long
        valorReg = registrosDict(clave)

        ' Nombre del registro
        rangoInicio.Offset(fila, 0).Value = clave

        ' Valor hexadecimal
        rangoInicio.Offset(fila, 1).Value = "0x" & Hex(valorReg)

        ' Valor decimal
        rangoInicio.Offset(fila, 2).Value = valorReg

        ' Formato de celda
        With rangoInicio.Offset(fila, 0).Resize(1, 3)
            .Borders.LineStyle = xlContinuous
            .HorizontalAlignment = xlCenter
        End With

        fila = fila + 1
    Next clave

    ' Ajustar ancho de columnas
    ws.Columns("F:H").AutoFit
End Sub

Function LeerRegistro(nombreReg As String) As Long
    ' ================================================
    ' LECTURA DE REGISTRO
    ' ================================================

    Dim regNormalizado As String
    regNormalizado = NormalizarNombreRegistro(nombreReg)

    ' Si el registro no existe, crearlo dinámicamente
    If Not registrosDict.Exists(regNormalizado) Then
        registrosDict.Add regNormalizado, 0&
        Call RenderizarRegistrosEnExcel  ' Actualizar visualización
    End If

    ' Retornar valor
    LeerRegistro = registrosDict(regNormalizado)

    ' Resaltar visualmente la lectura
    Call ResaltarRegistro(regNormalizado, COLOR_REGISTRO_LECTURA)
End Function

Sub EscribirRegistro(nombreReg As String, valor As Long)
    ' ================================================
    ' ESCRITURA DE REGISTRO
    ' ================================================

    Dim regNormalizado As String
    regNormalizado = NormalizarNombreRegistro(nombreReg)

    ' Actualizar o crear registro
    If registrosDict.Exists(regNormalizado) Then
        registrosDict(regNormalizado) = valor
    Else
        registrosDict.Add regNormalizado, valor
    End If

    ' Actualizar visualización
    Call RenderizarRegistrosEnExcel

    ' Resaltar visualmente la escritura
    Call ResaltarRegistro(regNormalizado, COLOR_REGISTRO_ESCRITURA)
End Sub

Sub ResaltarRegistro(nombreReg As String, colorRGB As Long)
    ' ================================================
    ' RESALTADO VISUAL DE REGISTRO
    ' ================================================

    Dim ws As Worksheet
    Set ws = ThisWorkbook.Worksheets("Hoja2")

    ' Buscar el registro en la tabla
    Dim rangoInicio As Range
    Set rangoInicio = ws.Range("F3")

    Dim fila As Long
    fila = 1

    Do While rangoInicio.Offset(fila, 0).Value <> ""
        If rangoInicio.Offset(fila, 0).Value = nombreReg Then
            ' Resaltar fila
            With rangoInicio.Offset(fila, 0).Resize(1, 3).Interior
                .Color = colorRGB
            End With

            ' Pausa para visualización
            Application.Wait (Now + TimeValue("0:00:00.3"))

            ' Restaurar color
            rangoInicio.Offset(fila, 0).Resize(1, 3).Interior.ColorIndex = xlNone
            Exit Sub
        End If
        fila = fila + 1
    Loop
End Sub
```

**Visualización en Excel:**

```
┌───────────┬──────────────┬──────────────┐
│ Registro  │ Valor (Hex)  │ Valor (Dec)  │
├───────────┼──────────────┼──────────────┤
│   RAX     │  0x00000009  │      9       │
│   RBX     │  0x0000000B  │      11      │
│   RCX     │  0x00000000  │      0       │
│   RDX     │  0x00000009  │      9       │
│   RSI     │  0x00000000  │      0       │
│   RDI     │  0x00000000  │      0       │
│   RBP     │  0x7FFFFFFE00│ 2147483648   │
│   RSP     │  0x7FFFFFFDD0│ 2147483600   │
│   R8      │  0x00000000  │      0       │
│   R9      │  0x00000000  │      0       │
│   ...     │     ...      │     ...      │
└───────────┴──────────────┴──────────────┘
```

---

### 2.7 Arquitectura Von Neumann

#### 2.7.1 Conceptualización

La arquitectura Von Neumann, propuesta por John von Neumann en 1945, es uno de los modelos fundamentales de arquitectura de computadoras. Se caracteriza por el uso de una **memoria unificada** que almacena tanto instrucciones como datos, accedidos a través de un **bus único**.

**Principios fundamentales:**

1. **Stored-Program Concept**: Las instrucciones se almacenan en memoria como datos
2. **Memoria Unificada**: Un único espacio de direcciones para código y datos
3. **Bus Compartido**: El mismo canal de comunicación para instrucciones y datos
4. **Secuencialidad**: Las instrucciones se ejecutan secuencialmente (salvo saltos)

#### 2.7.2 Características Principales

**Diagrama Conceptual de Arquitectura Von Neumann:**

```
┌──────────────────────────────────────────────────┐
│                   CPU                            │
│  ┌────────────┐         ┌─────────────┐         │
│  │  Unidad de │◄───────►│     ALU     │         │
│  │   Control  │         │             │         │
│  └─────┬──────┘         └─────────────┘         │
│        │                                         │
│  ┌─────▼──────────────────────────────┐         │
│  │     Banco de Registros             │         │
│  └────────────────────────────────────┘         │
└────────────┬─────────────────────────────────────┘
             │
             │ BUS ÚNICO
             │ (Direcciones, Datos, Control)
             │
┌────────────▼─────────────────────────────────────┐
│           MEMORIA UNIFICADA                      │
│  ┌──────────────────┬──────────────────┐        │
│  │   Instrucciones  │      Datos       │        │
│  │   (Código)       │   (Variables)    │        │
│  └──────────────────┴──────────────────┘        │
└──────────────────────────────────────────────────┘
```

**Componentes Fundamentales:**

1. **Unidad Central de Procesamiento (CPU)**:

   - Unidad de Control (UC): Coordina todas las operaciones
   - Unidad Aritmético-Lógica (ALU): Ejecuta operaciones
   - Banco de Registros: Almacenamiento ultrarrápido

2. **Memoria Principal (RAM)**:

   - Almacenamiento unificado para código y datos
   - Mismo espacio de direcciones
   - Acceso mediante bus compartido

3. **Sistema de Bus Único**:
   - Bus de direcciones: Especifica ubicación en memoria
   - Bus de datos: Transporta información
   - Bus de control: Señales de sincronización

**Flujo de Operación:**

```
┌─────────────────────────────────────────┐
│  1. UC lee dirección del PC             │
└─────────────┬───────────────────────────┘
              │
              ▼
┌─────────────────────────────────────────┐
│  2. Envía dirección por bus a memoria   │
└─────────────┬───────────────────────────┘
              │
              ▼
┌─────────────────────────────────────────┐
│  3. Memoria retorna instrucción         │
└─────────────┬───────────────────────────┘
              │
              ▼
┌─────────────────────────────────────────┐
│  4. UC decodifica instrucción           │
└─────────────┬───────────────────────────┘
              │
              ▼
┌─────────────────────────────────────────┐
│  5. Si necesita datos, repite pasos 1-3 │
│     (usa el MISMO bus)                  │
└─────────────┬───────────────────────────┘
              │
              ▼
┌─────────────────────────────────────────┐
│  6. Ejecuta en ALU                      │
└─────────────┬───────────────────────────┘
              │
              ▼
┌─────────────────────────────────────────┐
│  7. Escribe resultado (usa bus otra vez)│
└─────────────────────────────────────────┘
```

#### 2.7.3 Ventajas y Desventajas

**✅ VENTAJAS de la Arquitectura Von Neumann:**

| Ventaja                       | Descripción                                              | Impacto                           |
| ----------------------------- | -------------------------------------------------------- | --------------------------------- |
| **Simplicidad de Diseño**     | Un solo bus reduce la complejidad del hardware           | Menor costo de fabricación        |
| **Flexibilidad de Memoria**   | La distribución entre código y datos es dinámica         | Mejor aprovechamiento del espacio |
| **Código Automodificable**    | Los programas pueden modificar sus propias instrucciones | Útil para compiladores JIT        |
| **Facilidad de Programación** | Modelo de memoria unificado simplifica el desarrollo     | Menor complejidad en software     |
| **Economía**                  | Menos componentes físicos necesarios                     | Reducción de costos               |

**❌ DESVENTAJAS de la Arquitectura Von Neumann:**

| Desventaja                                     | Descripción                                                 | Impacto                       |
| ---------------------------------------------- | ----------------------------------------------------------- | ----------------------------- |
| **Cuello de Botella (Von Neumann Bottleneck)** | El bus compartido limita el ancho de banda                  | Rendimiento reducido          |
| **Acceso Secuencial**                          | No puede buscar instrucción y acceder datos simultáneamente | Mayor latencia                |
| **Conflictos de Bus**                          | Instrucciones y datos compiten por el mismo recurso         | Ciclos desperdiciados         |
| **Menor Throughput**                           | Comparado con arquitectura Harvard                          | Peor rendimiento en pipelines |
| **Vulnerabilidad de Seguridad**                | Buffer overflow puede sobrescribir código                   | Riesgo de seguridad           |

**Comparación Detallada: Von Neumann vs Harvard:**

```
╔═══════════════════════════════════════════════════════════════╗
║           ARQUITECTURA VON NEUMANN (Este Simulador)           ║
╠═══════════════════════════════════════════════════════════════╣
║                                                               ║
║  Características:                                             ║
║  • Memoria unificada para código y datos                     ║
║  • Bus único compartido                                       ║
║  • Acceso secuencial a memoria                               ║
║                                                               ║
║  Ventajas:                                                    ║
║  ✓ Diseño simple y económico                                 ║
║  ✓ Flexibilidad en uso de memoria                            ║
║  ✓ Facilita programación                                     ║
║                                                               ║
║  Desventajas:                                                 ║
║  ✗ Cuello de botella en el bus                               ║
║  ✗ No permite acceso paralelo                                ║
║  ✗ Menor rendimiento potencial                               ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝

╔═══════════════════════════════════════════════════════════════╗
║              ARQUITECTURA HARVARD (Referencia)                ║
╠═══════════════════════════════════════════════════════════════╣
║                                                               ║
║  Características:                                             ║
║  • Memorias separadas para código y datos                    ║
║  • Buses independientes                                       ║
║  • Acceso paralelo posible                                    ║
║                                                               ║
║  Ventajas:                                                    ║
║  ✓ Mayor ancho de banda                                      ║
║  ✓ Acceso simultáneo a instrucciones y datos                 ║
║  ✓ Mejor rendimiento en pipelines                            ║
║                                                               ║
║  Desventajas:                                                 ║
║  ✗ Mayor complejidad de hardware                             ║
║  ✗ Uso menos flexible de memoria                             ║
║  ✗ Mayor costo de implementación                             ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝
```

**El Cuello de Botella de Von Neumann:**

```
Tiempo (Ciclos) →

Sin Cuello de Botella (Harvard):
Ciclo 1: [Fetch Instr.] + [Read Data]  ← Paralelo
Ciclo 2: [Fetch Instr.] + [Read Data]  ← Paralelo
Ciclo 3: [Fetch Instr.] + [Write Data] ← Paralelo

Con Cuello de Botella (Von Neumann):
Ciclo 1: [Fetch Instr.]
Ciclo 2: [Read Data]     ← Debe esperar
Ciclo 3: [Fetch Instr.]
Ciclo 4: [Write Data]    ← Debe esperar
Ciclo 5: [Fetch Instr.]

Resultado: 40% más lento en este ejemplo
```

#### 2.7.4 Implementación en el Simulador

**Características de Nuestra Implementación:**

Nuestro simulador implementa una **arquitectura Von Neumann pura** con las siguientes decisiones de diseño:

1. **Memoria Unificada Global:**

```vba
' =====================================================
' MEMORIA UNIFICADA VON NEUMANN
' =====================================================
' Una única estructura de datos para TODO:
' - Instrucciones del programa
' - Variables y datos
' - Stack
' - Heap

Public memoriaStackGlobal As Object  ' Scripting.Dictionary

Sub InicializarMemoriaVonNeumann()
    ' Crear memoria unificada
    Set memoriaStackGlobal = CreateObject("Scripting.Dictionary")

    ' Esta memoria contiene TANTO instrucciones COMO datos
    ' Ejemplo de contenido:
    ' memoriaStackGlobal("MEM_0x1000") = "movl $10, %eax"  ← Instrucción
    ' memoriaStackGlobal("MEM_0x2000") = 42                ← Dato

    Debug.Print "Memoria Von Neumann inicializada"
    Debug.Print "Espacio unificado para código y datos"
End Sub
```

2. **Bus Compartido Simulado:**

```vba
' =====================================================
' SIMULACIÓN DEL BUS ÚNICO
' =====================================================
' En Von Neumann, instrucciones y datos compiten por el bus

Sub AccederBusMemoria(tipoAcceso As String, direccion As Long, _
                      Optional dato As Variant)
    ' Visualizar uso del bus
    Shape_Bus.Fill.ForeColor.RGB = COLOR_BUS_ACTIVO

    Select Case tipoAcceso
        Case "FETCH"
            ' Bus ocupado trayendo instrucción
            Debug.Print "BUS: Fetch instrucción desde " & Hex(direccion)
            Application.Wait (Now + TimeValue("0:00:00.3"))

        Case "READ"
            ' Bus ocupado leyendo dato
            Debug.Print "BUS: Read dato desde " & Hex(direccion)
            Application.Wait (Now + TimeValue("0:00:00.3"))

        Case "WRITE"
            ' Bus ocupado escribiendo dato
            Debug.Print "BUS: Write dato a " & Hex(direccion)
            Application.Wait (Now + TimeValue("0:00:00.3"))
    End Select

    ' Restaurar estado del bus
    Shape_Bus.Fill.ForeColor.RGB = COLOR_BUS_INACTIVO
End Sub
```

3. **Conflictos de Acceso:**

```vba
' =====================================================
' DEMOSTRACIÓN DEL CUELLO DE BOTELLA
' =====================================================

Sub DemostrarCuelloBotella()
    Dim ciclo As Long

    MsgBox "DEMOSTRACIÓN: Cuello de Botella Von Neumann" & vbCrLf & _
           "Observe cómo el bus se usa secuencialmente", vbInformation

    ' Instrucción: movl -4(%rbp), %eax
    ' Necesita: 1) Fetch instrucción, 2) Read dato

    ciclo = 1
    Debug.Print "=== Ciclo " & ciclo & " ==="
    Call AccederBusMemoria("FETCH", PC)  ' Bus ocupado con instrucción

    ciclo = 2
    Debug.Print "=== Ciclo " & ciclo & " ==="
    ' NO podemos leer el dato en el mismo ciclo
    ' Debemos esperar a que el bus esté libre
    Call AccederBusMemoria("READ", LeerRegistro("RBP") - 4)

    MsgBox "Total: 2 ciclos usados" & vbCrLf & _
           "Con Harvard: 1 ciclo (paralelo)" & vbCrLf & _
           "Penalización: 100%", vbInformation
End Sub
```

4. **Espacio de Direcciones Compartido:**

```vba
' =====================================================
' ESPACIO DE DIRECCIONES UNIFICADO
' =====================================================

Function ObtenerTipoDireccion(direccion As Long) As String
    ' En Von Neumann, el mismo espacio contiene todo
    ' Usamos convenciones para diferenciar:

    Select Case direccion
        Case Is < &H1000
            ObtenerTipoDireccion = "CÓDIGO"

        Case &H1000 To &H5000
            ObtenerTipoDireccion = "DATOS"

        Case Is > &H7FFFFFF00000
            ObtenerTipoDireccion = "STACK"

        Case Else
            ObtenerTipoDireccion = "HEAP"
    End Select

    ' NOTA: Esta es solo una convención
    ' En Von Neumann real, no hay distinción física
End Function
```

5. **Visualización del Modelo:**

```vba
Sub VisualizarArquitecturaVonNeumann()
    ' Crear diagrama visual en Excel
    Dim ws As Worksheet
    Set ws = ThisWorkbook.Worksheets("Arquitectura")

    ' Título
    ws.Range("B2").Value = "ARQUITECTURA VON NEUMANN"
    ws.Range("B2").Font.Bold = True
    ws.Range("B2").Font.Size = 16

    ' CPU
    With ws.Shapes.AddShape(msoShapeRectangle, 100, 50, 200, 100)
        .TextFrame.Characters.Text = "CPU" & vbCrLf & _
                                     "(UC + ALU + Registros)"
        .Fill.ForeColor.RGB = RGB(200, 220, 255)
    End With

    ' Bus
    With ws.Shapes.AddLine(200, 160, 200, 200)
        .Line.Weight = 3
        .Line.ForeColor.RGB = RGB(255, 100, 100)
    End With

    ws.Range("C12").Value = "BUS ÚNICO"
    ws.Range("C12").Font.Color = RGB(255, 0, 0)
    ws.Range("C12").Font.Italic = True

    ' Memoria
    With ws.Shapes.AddShape(msoShapeRectangle, 100, 210, 200, 80)
        .TextFrame.Characters.Text = "MEMORIA UNIFICADA" & vbCrLf & _
                                     "(Código + Datos)"
        .Fill.ForeColor.RGB = RGB(255, 230, 200)
    End With

    MsgBox "Diagrama de Arquitectura Von Neumann creado", vbInformation
End Sub
```

**Ejemplo Práctico de Limitación:**

```vba
Sub EjemploCuelloBotella()
    ' Programa ejemplo:
    ' movl $10, -4(%rbp)    ← Necesita fetch + write
    ' movl -4(%rbp), %eax   ← Necesita fetch + read
    ' addl $5, %eax         ← Necesita fetch + read (inmediato)

    Dim ciclosTotal As Long
    ciclosTotal = 0

    ' Instrucción 1
    Call AccederBusMemoria("FETCH", PC)       ' Ciclo 1
    ciclosTotal = ciclosTotal + 1
    Call AccederBusMemoria("WRITE", &H1000)   ' Ciclo 2
    ciclosTotal = ciclosTotal + 1

    ' Instrucción 2
    Call AccederBusMemoria("FETCH", PC + 1)   ' Ciclo 3
    ciclosTotal = ciclosTotal + 1
    Call AccederBusMemoria("READ", &H1000)    ' Ciclo 4
    ciclosTotal = ciclosTotal + 1

    ' Instrucción 3
    Call AccederBusMemoria("FETCH", PC + 2)   ' Ciclo 5
    ciclosTotal = ciclosTotal + 1
    ' El inmediato está en la instrucción, no necesita acceso extra

    MsgBox "Von Neumann: " & ciclosTotal & " ciclos" & vbCrLf & _
           "Harvard (teórico): 3 ciclos" & vbCrLf & _
           "Diferencia: " & (ciclosTotal - 3) & " ciclos", vbInformation
End Sub
```

**Ventajas de Nuestra Implementación Von Neumann:**

1. **Simplicidad Educativa:**

   - Más fácil de entender para estudiantes
   - Código VBA más simple y mantenible
   - Visualización clara del cuello de botella

2. **Realismo:**

   - Representa la mayoría de sistemas x86 reales
   - Muestra las limitaciones reales de rendimiento
   - Permite entender por qué existen las cachés

3. **Flexibilidad:**
   - Fácil modificar distribución memoria código/datos
   - Permite código automodificable (avanzado)
   - Simplifica la gestión de memoria dinámica

**Tabla Comparativa Final:**

| Aspecto                  | Von Neumann (Implementado) | Harvard (Referencia)       |
| ------------------------ | -------------------------- | -------------------------- |
| **Buses**                | 1 compartido               | 2 separados                |
| **Memoria**              | Unificada                  | Dividida                   |
| **Accesos Paralelos**    | No                         | Sí                         |
| **Complejidad VBA**      | Baja                       | Alta                       |
| **Realismo x86**         | Alto                       | Bajo                       |
| **Didáctica**            | Excelente                  | Confusa para principiantes |
| **Rendimiento Simulado** | Realista (con bottleneck)  | Mejor pero irreal          |

---

### 2.8 Ciclo de Instrucción

#### 2.8.1 Conceptualización

El ciclo de instrucción es la secuencia completa de microoperaciones que realiza un procesador para ejecutar una única instrucción de máquina. Representa el nivel más básico del funcionamiento del CPU.

**Definición Formal:**

> El ciclo de instrucción es el proceso iterativo mediante el cual el procesador:
>
> 1. Obtiene (fetch) una instrucción de memoria
> 2. La decodifica (decode)
> 3. La ejecuta (execute)
> 4. Accede a memoria si es necesario (memory access)
> 5. Escribe los resultados (write back)

**Componentes del Ciclo:**

```
┌─────────────────────────────────────────────┐
│         CICLO DE INSTRUCCIÓN COMPLETO       │
│              (5 ETAPAS)                     │
└─────────────────────────────────────────────┘

Etapa 1: IF  (Instruction Fetch)
Etapa 2: ID  (Instruction Decode)
Etapa 3: EX  (Execute)
Etapa 4: MEM (Memory Access)
Etapa 5: WB  (Write Back)

         ┌──────┐
    ┌───►│  IF  │
    │    └───┬──┘
    │        │
    │    ┌───▼──┐
    │    │  ID  │
    │    └───┬──┘
    │        │
    │    ┌───▼──┐
    │    │  EX  │
    │    └───┬──┘
    │        │
    │    ┌───▼──┐
    │    │ MEM  │
    │    └───┬──┘
    │        │
    │    ┌───▼──┐
    │    │  WB  │
    │    └───┬──┘
    │        │
    └────────┘
    (Repetir)
```

#### 2.8.2 Fases del Ciclo

**FASE 1: INSTRUCTION FETCH (IF)**

```
┌─────────────────────────────────────────────┐
│  ETAPA IF: BÚSQUEDA DE INSTRUCCIÓN         │
├─────────────────────────────────────────────┤
│                                             │
│  Pasos:                                     │
│  1. Leer el valor del PC                   │
│  2. Enviar dirección al bus                │
│  3. Consultar I-Cache                       │
│     ├─ HIT: Obtener instrucción            │
│     └─ MISS: Acceder RAM → Cargar caché   │
│  4. Cargar instrucción en IR                │
│  5. Incrementar PC (PC = PC + 1)           │
│  6. Actualizar Fetch Buffer                 │
│                                             │
│  Tiempo: 1 ciclo (hit) / 4-10 ciclos (miss)│
└─────────────────────────────────────────────┘
```

```vba
Sub Fetch()
    ' =============================================
    ' ETAPA 1: INSTRUCTION FETCH (IF)
    ' =============================================

    ' Paso 1: Leer Program Counter
    Dim direccionPC As Long
    direccionPC = PC

    ' Visualización
    CELDA_PC.Value = "0x" & Hex(direccionPC)
    Call ResaltarTemporal(CELDA_PC, COLOR_FETCH, 0.5)

    ' Paso 2: Calcular fila en Excel (memoria)
    Dim filaInstruccion As Long
    filaInstruccion = 3 + direccionPC  ' Offset base

    ' Paso 3: Buscar en I-Cache primero
    Dim instruccion As String
    Dim cacheHit As Boolean

    cacheHit = BuscarEnCache(RANGO_I_CACHE, CStr(direccionPC), instruccion)

    If cacheHit Then
        ' Cache Hit
        EstadoCache_Shape.TextFrame.Characters.Text = "I-CACHE HIT"
        EstadoCache_Shape.Fill.ForeColor.RGB = COLOR_CACHE_HIT
    Else
        ' Cache Miss - Acceder a RAM
        EstadoCache_Shape.TextFrame.Characters.Text = "I-CACHE MISS"
        EstadoCache_Shape.Fill.ForeColor.RGB = COLOR_CACHE_MISS

        ' Penalización de latencia
        Application.Wait (Now + TimeValue("0:00:01"))

        ' Leer de memoria principal (Hoja2)
        instruccion = Hoja2.Cells(filaInstruccion, 1).Value

        ' Cargar en I-Cache
        Call CargarEnCache(RANGO_I_CACHE, _
                          "Addr:" & direccionPC & " | " & instruccion)
    End If

    ' Paso 4: Cargar en Instruction Register
    CELDA_IR.Value = instruccion
    Call ResaltarTemporal(CELDA_IR, COLOR_IR_ACTIVO, 0.5)

    ' Paso 5: Actualizar Fetch Buffer
    RANGO_FETCH_BUFFER.Cells(1, 1).Value = instruccion
    Call ResaltarTemporal(RANGO_FETCH_BUFFER, COLOR_BUFFER, 0.3)

    ' Paso 6: Incrementar PC
    PC = PC + 1

    Debug.Print "FETCH: " & instruccion
End Sub
```

**FASE 2: INSTRUCTION DECODE (ID)**

```
┌─────────────────────────────────────────────┐
│  ETAPA ID: DECODIFICACIÓN DE INSTRUCCIÓN   │
├─────────────────────────────────────────────┤
│                                             │
│  Pasos:                                     │
│  1. Leer instrucción desde IR               │
│  2. Parsear sintaxis AT&T                   │
│  3. Identificar opcode                      │
│  4. Extraer operandos (src, dest)          │
│  5. Detectar dependencias (hazards)         │
│  6. Preparar señales de control             │
│  7. Cargar en Decode Buffer                 │
│                                             │
│  Tiempo: 1 ciclo                            │
└─────────────────────────────────────────────┘
```

```vba
Sub Decode()
    ' =============================================
    ' ETAPA 2: INSTRUCTION DECODE (ID)
    ' =============================================

    ' Paso 1: Leer instrucción desde IR
    Dim instruccion As String
    instruccion = CELDA_IR.Value

    If Trim(instruccion) = "" Then Exit Sub

    ' Visualización
    OpCode_Shape.Fill.ForeColor.RGB = COLOR_DECODE

    ' Paso 2: Parsear instrucción
    Dim opcode As String, operando1 As String, operando2 As String
    Call ParsearInstruccionDirecta(instruccion, opcode, operando1, operando2)

    ' Paso 3: Extraer y mostrar opcode
    OpCode_Shape.TextFrame.Characters.Text = UCase(opcode)
    Call ResaltarTemporal(OpCode_Shape, COLOR_OPCODE, 0.5)

    ' Paso 4: Extraer y mostrar operandos
    Operandos_Shape.TextFrame.Characters.Text = operando1 & ", " & operando2
    Call ResaltarTemporal(Operandos_Shape, COLOR_OPERANDOS, 0.5)

    ' Paso 5: Identificar registros involucrados
    Dim regDestino As String, regsFuente As String
    Call ExtraerRegistros(instruccion, regDestino, regsFuente)

    ' Paso 6: Cargar en Decode Buffer
    RANGO_DECODE_BUFFER.Cells(1, 1).Value = opcode
    RANGO_DECODE_BUFFER.Cells(1, 2).Value = operando1
    RANGO_DECODE_BUFFER.Cells(1, 3).Value = operando2
    Call ResaltarTemporal(RANGO_DECODE_BUFFER, COLOR_BUFFER, 0.3)

    ' Paso 7: Generar señales de control (conceptual)
    Select Case UCase(opcode)
        Case "MOV", "MOVL", "MOVQ"
            ' Señal: ALU_OP = PASS, MEM_READ = 0, MEM_WRITE = 0
            Debug.Print "Señales: ALU_PASS, REG_WRITE"

        Case "ADD", "ADDL"
            ' Señal: ALU_OP = ADD, MEM_READ = 0, MEM_WRITE = 0
            Debug.Print "Señales: ALU_ADD, REG_WRITE"

        Case "PUSH", "PUSHQ"
            ' Señal: ALU_OP = SUB (RSP), MEM_WRITE = 1
            Debug.Print "Señales: ALU_SUB, MEM_WRITE"

        ' ... más casos
    End Select

    Debug.Print "DECODE: " & opcode & " " & operando1 & ", " & operando2
End Sub
```

**FASE 3: EXECUTE (EX)**

```
┌─────────────────────────────────────────────┐
│  ETAPA EX: EJECUCIÓN                        │
├─────────────────────────────────────────────┤
│                                             │
│  Pasos:                                     │
│  1. Leer operandos (registros/memoria/imm) │
│  2. Enviar operandos a entradas de ALU      │
│  3. Seleccionar operación en ALU            │
│  4. Ejecutar operación                      │
│  5. Generar resultado                       │
│  6. Actualizar flags (ZF, SF, CF, OF)      │
│  7. Almacenar en registro temporal (Z1/Z2) │
│                                             │
│  Tiempo: 1 ciclo (operaciones básicas)      │
│          3-40 ciclos (MUL/DIV)              │
└─────────────────────────────────────────────┘
```

```vba
Sub Execute()
    ' =============================================
    ' ETAPA 3: EXECUTE (EX)
    ' =============================================

    ' Leer desde Decode Buffer
    Dim opcode As String, operando1 As String, operando2 As String
    opcode = RANGO_DECODE_BUFFER.Cells(1, 1).Value
    operando1 = RANGO_DECODE_BUFFER.Cells(1, 2).Value
    operando2 = RANGO_DECODE_BUFFER.Cells(1, 3).Value

    If Trim(opcode) = "" Then Exit Sub

    ' Construir instrucción completa
    Dim instruccionCompleta As String
    instruccionCompleta = opcode & " " & operando1
    If Trim(operando2) <> "" Then
        instruccionCompleta = instruccionCompleta & ", " & operando2
    End If

    ' Ejecutar en ALU
    Call EjecutarEnALU(instruccionCompleta)

    Debug.Print "EXECUTE: Operación ejecutada en ALU"
End Sub
```

**FASE 4: MEMORY ACCESS (MEM)**

```
┌─────────────────────────────────────────────┐
│  ETAPA MEM: ACCESO A MEMORIA                │
├─────────────────────────────────────────────┤
│                                             │
│  Casos:                                     │
│                                             │
│  LOAD (Lectura):                            │
│  1. Calcular dirección efectiva             │
│  2. Buscar en D-Cache                       │
│     ├─ HIT: Obtener dato                   │
│     └─ MISS: Acceder RAM → Cargar caché   │
│  3. Colocar dato en Z1                      │
│                                             │
│  STORE (Escritura):                         │
│  1. Calcular dirección efectiva             │
│  2. Escribir en D-Cache                     │
│  3. Actualizar RAM (write-through)          │
│                                             │
│  OTRAS INSTRUCCIONES:                       │
│  - Pasar resultado de ALU sin cambios       │
│                                             │
│  Tiempo: 1 ciclo (hit) / 4-10 ciclos (miss) │
└─────────────────────────────────────────────┘
```

```vba
Sub MemoryAccess()
    ' =============================================
    ' ETAPA 4: MEMORY ACCESS (MEM)
    ' =============================================

    Dim opcode As String
    opcode = RANGO_DECODE_BUFFER.Cells(1, 1).Value

    If Trim(opcode) = "" Then Exit Sub

    ' Determinar si necesita acceso a memoria
    Select Case UCase(opcode)
        Case "MOV", "MOVL", "MOVQ"
            ' Verificar si el operando fuente es memoria
            Dim operando2 As String
            operando2 = RANGO_DECODE_BUFFER.Cells(1, 3).Value

            If InStr(operando2, "(") > 0 Then
                ' Es acceso a memoria - LOAD
                Dim direccion As String
                direccion = operando2

                ' Buscar en D-Cache
                Dim dato As String
                Dim cacheHit As Boolean

                cacheHit = BuscarEnCache(RANGO_D_CACHE, direccion, dato)

                If cacheHit Then
                    EstadoDCache_Shape.TextFrame.Characters.Text = "D-CACHE HIT"
                    EstadoDCache_Shape.Fill.ForeColor.RGB = COLOR_CACHE_HIT
                Else
                    EstadoDCache_Shape.TextFrame.Characters.Text = "D-CACHE MISS"
                    EstadoDCache_Shape.Fill.ForeColor.RGB = COLOR_CACHE_MISS

                    ' Leer de RAM
                    dato = LeerMemoria(direccion)

                    ' Cargar en D-Cache
                    Call CargarEnCacheAcumulativo(RANGO_D_CACHE, _
                                                  "Addr:" & direccion & " | " & dato)
                End If

                Z1 = CLng(dato)
            End If

        Case "PUSH", "PUSHQ", "POP", "POPQ"
            ' Estas instrucciones ya manejaron memoria en Execute
            ' No hacemos nada adicional aquí

        Case Else
            ' No requiere acceso a memoria
            ' Z1 ya contiene el resultado de ALU
    End Select

    Debug.Print "MEM: Acceso a memoria completado"
End Sub
```

**FASE 5: WRITE BACK (WB)**

```
┌─────────────────────────────────────────────┐
│  ETAPA WB: ESCRITURA DE RESULTADOS          │
├─────────────────────────────────────────────┤
│                                             │
│  Pasos:                                     │
│  1. Leer resultado desde Z1/Z2              │
│  2. Identificar registro destino            │
│  3. Escribir en banco de registros          │
│  4. Actualizar visualización                │
│  5. Limpiar buffers temporales              │
│  6. Marcar instrucción como completada      │
│                                             │
│  Tiempo: 1 ciclo                            │
└─────────────────────────────────────────────┘
```

```vba
Sub WriteBack()
    ' =============================================
    ' ETAPA 5: WRITE BACK (WB)
    ' =============================================

    Dim operando1 As String
    operando1 = RANGO_DECODE_BUFFER.Cells(1, 2).Value

    If Trim(operando1) = "" Then Exit Sub

    ' Si el operando1 es un registro, escribir Z1 en él
    If Left(operando1, 1) = "%" Then
        ' Es un registro
        Dim nombreReg As String
        nombreReg = Replace(operando1, "%", "")

        ' Escribir resultado
        Call EscribirRegistro(nombreReg, Z1)

        Debug.Print "WB: " & Z1 & " → " & nombreReg
    ElseIf InStr(operando1, "(") > 0 Then
        ' Es dirección de memoria
        Call EscribirMemoria(operando1, Z1)

        Debug.Print "WB: " & Z1 & " → " & operando1
    End If

    ' Limpiar buffers
    RANGE_ALU_OUTPUT.ClearContents
    RANGO_DECODE_BUFFER.ClearContents
    RANGO_FETCH_BUFFER.ClearContents

    ' Resetear Z1/Z2
    Z1 = 0
    Z2 = 0

    Debug.Print "WB: Ciclo completado"
End Sub
```

#### 2.8.3 Diseño en el Simulador

**Función Principal del Ciclo:**

```vba
Sub AvanzarCiclo()
    ' =============================================
    ' EJECUCIÓN COMPLETA DE UN CICLO DE INSTRUCCIÓN
    ' =============================================

    On Error GoTo ErrorHandler

    ' Verificar que hay instrucciones
    Dim totalInstrucciones As Long
    totalInstrucciones = Hoja2.Cells(Hoja2.Rows.Count, 1).End(xlUp).Row - 2

    If PC >= totalInstrucciones Then
        MsgBox "Programa terminado. PC = " & PC, vbInformation
        Exit Sub
    End If

    ' Título de ciclo
    Debug.Print String(50, "=")
    Debug.Print "CICLO " & (PC + 1) & " - Instrucción en PC=" & PC
    Debug.Print String(50, "=")

    ' === ETAPA 1: FETCH ===
    Debug.Print vbCrLf & ">>> ETAPA 1: FETCH"
    Call Fetch()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' === ETAPA 2: DECODE ===
    Debug.Print vbCrLf & ">>> ETAPA 2: DECODE"
    Call Decode()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' === ETAPA 3: EXECUTE ===
    Debug.Print vbCrLf & ">>> ETAPA 3: EXECUTE"
    Call Execute()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' === ETAPA 4: MEMORY ACCESS ===
    Debug.Print vbCrLf & ">>> ETAPA 4: MEMORY ACCESS"
    Call MemoryAccess()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    ' === ETAPA 5: WRITE BACK ===
    Debug.Print vbCrLf & ">>> ETAPA 5: WRITE BACK"
    Call WriteBack()
    Application.Wait (Now + TimeValue("0:00:00.5"))

    Debug.Print vbCrLf & "Ciclo completado exitosamente" & vbCrLf

    Exit Sub

ErrorHandler:
    MsgBox "Error en ciclo de instrucción: " & Err.Description, vbCritical
    Debug.Print "ERROR: " & Err.Description
End Sub
```

**Diagrama de Flujo Visual:**

```
    INICIO
      │
      ▼
┌─────────────┐
│   FETCH     │ ◄── Leer PC, Buscar I-Cache
│    (IF)     │     Cargar IR, PC++
└──────┬──────┘
       │ Pausa 0.5s
       ▼
┌─────────────┐
│   DECODE    │ ◄── Parsear instrucción
│    (ID)     │     Extraer opcode/operandos
└──────┬──────┘
       │ Pausa 0.5s
       ▼
┌─────────────┐
│   EXECUTE   │ ◄── Ejecutar en ALU
│    (EX)     │     Actualizar flags
└──────┬──────┘
       │ Pausa 0.5s
       ▼
┌─────────────┐
│   MEMORY    │ ◄── Load/Store si aplica
│    (MEM)    │     Consultar D-Cache
└──────┬──────┘
       │ Pausa 0.5s
       ▼
┌─────────────┐
│ WRITE BACK  │ ◄── Escribir resultado
│    (WB)     │     Limpiar buffers
└──────┬──────┘
       │
       ▼
    ¿Más
instrucciones?
  │       │
 SÍ      NO
  │       │
  └──┐    └──► FIN
     │
     └─────► INICIO
```

---

### 2.9 Pipeline de Instrucciones

#### 2.9.1 Conceptualización

El pipeline de instrucciones es una técnica de implementación que permite la ejecución superpuesta de múltiples instrucciones. Cada etapa del ciclo de instrucción trabaja en una instrucción diferente simultáneamente, similar a una línea de ensamblaje.

**Analogía con Línea de Ensamblaje:**

```
FÁBRICA DE AUTOMÓVILES (sin pipeline):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Auto 1: [Motor] → [Carrocería] → [Pintura] → [Acabado] → [✓]
        Tiempo: 4 horas

Auto 2:                                                    [Motor] → ...
        Debe esperar a que Auto 1 termine completamente

Producción: 1 auto cada 4 horas

FÁBRICA CON PIPELINE:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Hora 1: Auto 1 [Motor]
Hora 2: Auto 1 [Carrocería] | Auto 2 [Motor]
Hora 3: Auto 1 [Pintura] | Auto 2 [Carrocería] | Auto 3 [Motor]
Hora 4: Auto 1 [Acabado] | Auto 2 [Pintura] | Auto 3 [Carrocería] | Auto 4 [Motor]
Hora 5: Auto 1 [✓] | Auto 2 [Acabado] | Auto 3 [Pintura] | Auto 4 [Carrocería] | Auto 5 [Motor]

Producción: 1 auto cada 1 hora (después del llenado inicial)
Speedup: 4×
```

**Aplicado a Procesadores:**

```
SIN PIPELINE (Ejecución Secuencial):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
I1: [IF][ID][EX][MEM][WB]
I2:                      [IF][ID][EX][MEM][WB]
I3:                                          [IF][ID][EX][MEM][WB]

Tiempo total: 15 ciclos para 3 instrucciones
CPI (Cycles Per Instruction): 5

CON PIPELINE (Ejecución Superpuesta):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ciclo: 1    2    3    4    5    6    7    8    9
I1:   [IF][ID][EX][MEM][WB]
I2:       [IF][ID][EX][MEM][WB]
I3:           [IF][ID][EX][MEM][WB]

Tiempo total: 9 ciclos para 3 instrucciones
CPI (ideal): 1
Speedup: ~1.67× (para 3 instrucciones)
```

#### 2.9.2 Beneficios del Pipeline

**1. Mayor Throughput (Rendimiento):**

```
Throughput = Número de instrucciones completadas / Tiempo total

Sin Pipeline:
  3 instrucciones / 15 ciclos = 0.2 instr/ciclo

Con Pipeline (ideal):
  3 instrucciones / 9 ciclos = 0.33 instr/ciclo

En estado estable (pipeline lleno):
  1 instrucción / ciclo = 1.0 instr/ciclo
```

**2. Menor CPI (Cycles Per Instruction):**

```
CPI = Ciclos totales / Número de instrucciones

Sin Pipeline: 15 / 3 = 5.0 CPI
Con Pipeline: 9 / 3 = 3.0 CPI
Pipeline ideal: → 1.0 CPI
```

**3. Mejor Utilización de Recursos:**

```
UTILIZACIÓN DE HARDWARE SIN PIPELINE:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ciclo:  1   2   3   4   5   6   7   8   9   10
IF:    [X]  .   .   .   .  [X]  .   .   .   .
ID:     .  [X]  .   .   .   .  [X]  .   .   .
EX:     .   .  [X]  .   .   .   .  [X]  .   .
MEM:    .   .   .  [X]  .   .   .   .  [X]  .
WB:     .   .   .   .  [X]  .   .   .   .  [X]

Utilización promedio: 20% (1/5 unidades activas)

UTILIZACIÓN CON PIPELINE:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ciclo:  1   2   3   4   5   6   7   8   9   10
IF:    [X] [X] [X] [X] [X] [X] [X] [X] [X] [X]
ID:     .  [X] [X] [X] [X] [X] [X] [X] [X] [X]
EX:     .   .  [X] [X] [X] [X] [X] [X] [X] [X]
MEM:    .   .   .  [X] [X] [X] [X] [X] [X] [X]
WB:     .   .   .   .  [X] [X] [X] [X] [X] [X]

Utilización promedio: 100% (después de llenado)
```

**4. Speedup Teórico:**

```
Speedup = Tiempo sin pipeline / Tiempo con pipeline
        = (N × k) / (k + N - 1)

Donde:
  N = Número de instrucciones
  k = Número de etapas del pipeline

Para N muy grande:
  Speedup → k (número de etapas)

Nuestro simulador (k=5):
  Speedup máximo teórico = 5×
```

#### 2.9.3 Estructura de 5 Etapas

**Tabla Completa de Ejecución:**

```
┌──────────────────────────────────────────────────────────────────────┐
│             PIPELINE DE 5 ETAPAS - EJECUCIÓN IDEAL                   │
├────────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┤
│ Ciclo  │ I1  │ I2  │ I3  │ I4  │ I5  │ I6  │ I7  │ I8  │ I9  │ I10 │
├────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│   1    │ IF  │     │     │     │     │     │     │     │     │     │
│   2    │ ID  │ IF  │     │     │     │     │     │     │     │     │
│   3    │ EX  │ ID  │ IF  │     │     │     │     │     │     │     │
│   4    │ MEM │ EX  │ ID  │ IF  │     │     │     │     │     │     │
│   5    │ WB  │ MEM │ EX  │ ID  │ IF  │     │     │     │     │     │
│   6    │  ✓  │ WB  │ MEM │ EX  │ ID  │ IF  │     │     │     │     │
│   7    │     │  ✓  │ WB  │ MEM │ EX  │ ID  │ IF  │     │     │     │
│   8    │     │     │  ✓  │ WB  │ MEM │ EX  │ ID  │ IF  │     │     │
│   9    │     │     │     │  ✓  │ WB  │ MEM │ EX  │ ID  │ IF  │     │
│  10    │     │     │     │     │  ✓  │ WB  │ MEM │ EX  │ ID  │ IF  │
│  11    │     │     │     │     │     │  ✓  │ WB  │ MEM │ EX  │ ID  │
│  12    │     │     │     │     │     │     │  ✓  │ WB  │ MEM │ EX  │
│  13    │     │     │     │     │     │     │     │  ✓  │ WB  │ MEM │
│  14    │     │     │     │     │     │     │     │     │  ✓  │ WB  │
└────────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘

Análisis:
• Primera instrucción completa: Ciclo 5
• Instrucciones completadas en ciclos 6-14: 1 por ciclo
• Throughput en estado estable: 1.0 instrucciones/ciclo
• Total: 10 instrucciones en 14 ciclos (vs 50 sin pipeline)
• Speedup real: 50/14 = 3.57×
```

**Llenado y Vaciado del Pipeline:**

```
FASE 1: LLENADO (Fill-up)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ciclos 1-4: El pipeline se está llenando
No hay instrucciones completándose aún
Utilización subóptima

FASE 2: ESTADO ESTABLE (Steady State)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ciclos 5-10: Pipeline lleno
1 instrucción completada por ciclo
Máxima eficiencia

FASE 3: VACIADO (Drain)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Ciclos 11-14: Pipeline vaciándose
No entran nuevas instrucciones
Aún hay instrucciones completándose
```

#### 2.9.4 Diseño en el Simulador

**Estructura de Datos:**

```vba
' =====================================================
' ESTRUCTURA DE INSTRUCCIÓN EN PIPELINE
' =====================================================

Type InstruccionPipeline
    instruccion As String        ' Texto completo de la instrucción
    etapa As String              ' "IF", "ID", "EX", "MEM", "WB"
    RegistroDestino As String    ' Registro que se escribe
    registrosFuente As String    ' Registros que se leen
    ciclo As Long                ' Ciclo en que entró al pipeline
    numeroInstruccion As Long    ' Número de instrucción (orden)
End Type

' Array del pipeline (una entrada por etapa)
Dim pipeline(1 To 5) As InstruccionPipeline
```

**Función Principal del Simulador de Pipeline:**

```vba
Sub SimularPipelineCPU(rangoInstrucciones As Range, rangoPipeline As Range)
    ' =====================================================
    ' SIMULACIÓN COMPLETA DEL PIPELINE
    ' =====================================================

    Dim ciclo As Long, pc As Long, totalInstrucciones As Long
    Dim hayHazard As Boolean

    ciclo = 0
    pc = 1
    totalInstrucciones = rangoInstrucciones.Rows.Count

    ' Limpiar pipeline
    Dim i As Integer
    For i = 1 To 5
        pipeline(i).instruccion = ""
        pipeline(i).etapa = ""
    Next i

    ' Bucle principal
    Do While (pc <= totalInstrucciones) Or HayInstruccionesEnPipeline(pipeline)
        ciclo = ciclo + 1
        hayHazard = False

        ' Procesar WB → MEM → EX → ID → IF
        ' (orden inverso para evitar sobrescritura)

        If pipeline(5).instruccion <> "" Then
            ' Write Back
            Call ProcesarWB(pipeline(5), rangoPipeline, ciclo)
            pipeline(5).instruccion = ""
        End If

        If pipeline(4).instruccion <> "" Then
            ' Memory Access
            Call ProcesarMEM(pipeline(4), rangoPipeline, ciclo)
            pipeline(5) = pipeline(4)
            pipeline(4).instruccion = ""
        End If

        If pipeline(3).instruccion <> "" Then
            ' Execute
            Call ProcesarEX(pipeline(3), rangoPipeline, ciclo)
            pipeline(4) = pipeline(3)
            pipeline(3).instruccion = ""
        End If

        If pipeline(2).instruccion <> "" Then
            ' Instruction Decode + Detección de Hazards
            hayHazard = DetectarHazard(pipeline(2), pipeline(3), pipeline(4))

            If hayHazard Then
                Call InsertarStall(pipeline(2), rangoPipeline, ciclo)
            Else
                Call ProcesarID(pipeline(2), rangoPipeline, ciclo)
                pipeline(3) = pipeline(2)
                pipeline(2).instruccion = ""
            End If
        End If

        If pc <= totalInstrucciones And Not hayHazard Then
            ' Instruction Fetch
            Dim nuevaInstr As String
            nuevaInstr = rangoInstrucciones.Cells(pc, 1).Value

            If Trim(nuevaInstr) <> "" Then
                pipeline(1).instruccion = nuevaInstr
                pipeline(1).numeroInstruccion = pc
                Call ExtraerRegistros(nuevaInstr, _
                                     pipeline(1).RegistroDestino, _
                                     pipeline(1).registrosFuente)

                Call ProcesarIF(pipeline(1), rangoPipeline, ciclo)
                pipeline(2) = pipeline(1)
                pipeline(1).instruccion = ""
                pc = pc + 1
            End If
        End If

        Application.Wait Now + TimeValue("00:00:01")
        DoEvents
    Loop

    MsgBox "Pipeline completado: " & totalInstrucciones & " instrucciones en " & ciclo & " ciclos", vbInformation
End Sub
```

---

## 🏗️ Arquitectura del Simulador

### 3.1 Visión de Alto Nivel

El simulador está estructurado en tres capas principales que separan responsabilidades:

```
╔════════════════════════════════════════════════════════╗
║          CAPA DE PRESENTACIÓN (Excel UI)               ║
╠════════════════════════════════════════════════════════╣
║  • Hojas de cálculo (Hoja1, Hoja2)                    ║
║  • Shapes y objetos gráficos                           ║
║  • Tablas de visualización                             ║
║  • Rangos nombrados (CELDA_PC, RANGO_I_CACHE, etc.)   ║
║  • Botones y controles de usuario                      ║
╚════════════════════════════════════════════════════════╝
                        ↕
╔════════════════════════════════════════════════════════╗
║           CAPA DE CONTROL (VBA Modules)                ║
╠════════════════════════════════════════════════════════╣
║  • Módulo1: Visualización del pipeline                 ║
║  • Módulo2: Motor de simulación                        ║
║  • Módulo3: Sistema de registros                       ║
║  • Módulo4: ALU y operaciones                          ║
║  • Módulo5: Gestión de memoria                         ║
║  • Módulo6: Sistema de caché                           ║
║  • Módulo7: Unidad de control                          ║
║  • Módulo8: Parser de ensamblador                      ║
║  • Módulo9: Utilidades y helpers                       ║
╚════════════════════════════════════════════════════════╝
                        ↕
╔════════════════════════════════════════════════════════╗
║              CAPA DE DATOS (Almacenamiento)            ║
╠════════════════════════════════════════════════════════╣
║  • memoriaStackGlobal (Scripting.Dictionary)          ║
║  • registrosDict (Scripting.Dictionary)                ║
║  • Variables globales (PC, Z1, Z2, Flags)             ║
║  • Cachés (celdas de Excel como almacenamiento)        ║
╚════════════════════════════════════════════════════════╝
```

### 3.2 Diagrama de Flujo de Datos

```
┌─────────────────────────────────────────────────────────┐
│  1. ENTRADA DE USUARIO                                  │
│     ├─ Código ensamblador en Hoja1 (celda B3)         │
│     └─ Presionar botón "Cargar Ensamblador"           │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  2. CARGA Y NORMALIZACIÓN                               │
│     ├─ CargarEnsamblador()                             │
│     ├─ Normalizar líneas (quitar espacios)             │
│     ├─ Copiar a Hoja2 (columna A, fila 3+)            │
│     └─ InicializarSistemaRegistros()                   │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  3. INICIALIZACIÓN                                      │
│     ├─ Crear memoriaStackGlobal (Dictionary)           │
│     ├─ Detectar registros usados                       │
│     ├─ Limpiar cachés (I-Cache, D-Cache)              │
│     ├─ Resetear PC = 0                                 │
│     └─ Renderizar interfaz inicial                     │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  4. EJECUCIÓN (Usuario elige modo)                     │
│     ├─ OPCIÓN A: AvanzarCiclo()                       │
│     │   └─ Ejecuta 1 instrucción (5 etapas) paso a paso│
│     └─ OPCIÓN B: SimularPipelineCPU()                 │
│         └─ Ejecuta todas las instrucciones con pipeline│
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  5. CICLO DE INSTRUCCIÓN                                │
│     ├─ Fetch() → Decode() → Execute() → MEM() → WB()  │
│     ├─ Actualización de registros                       │
│     ├─ Actualización de memoria                         │
│     └─ Actualización de cachés                          │
└────────────────────┬────────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────────┐
│  6. VISUALIZACIÓN EN TIEMPO REAL                        │
│     ├─ Resaltar celdas activas                         │
│     ├─ Actualizar shapes (PC, IR, ALU, Flags)          │
│     ├─ Colorear etapas del pipeline                     │
│     └─ Mostrar tabla de memoria/registros               │
└─────────────────────────────────────────────────────────┘
```

### 3.3 Componentes del Sistema

#### 3.3.1 Estructura de Hojas

| Hoja             | Propósito            | Contenido Principal                                       |
| ---------------- | -------------------- | --------------------------------------------------------- |
| **Hoja1**        | Entrada de código    | Celda B3: Código ensamblador del usuario                  |
| **Hoja2**        | Simulación principal | Código normalizado, registros, visualización del pipeline |
| **Memoria**      | Visualización de RAM | Tabla ordenada con direcciones y valores                  |
| **Arquitectura** | Diagrama educativo   | Representación gráfica de Von Neumann                     |

#### 3.3.2 Rangos Nombrados Principales

```vba
' Unidad de Control
Const CELDA_PC = "Hoja2!L3"
Const CELDA_IR = "Hoja2!L5"
Const CELDA_MAR = "Hoja2!L7"
Const CELDA_MDR = "Hoja2!L9"

' ALU
Const RANGE_ALU_INPUT1 = "Hoja2!P3"
Const RANGE_ALU_INPUT2 = "Hoja2!P5"
Const RANGE_ALU_OUTPUT = "Hoja2!P7"

' Buffers
Const RANGO_FETCH_BUFFER = "Hoja2!T3:T5"
Const RANGO_DECODE_BUFFER = "Hoja2!T7:T9"

' Cachés
Const RANGO_I_CACHE = "Hoja2!X3:X10"
Const RANGO_D_CACHE = "Hoja2!X12:X19"
Const RANGO_L2_CACHE = "Hoja2!X21:X28"

' Memoria
Const RANGO_MEMORIA_PRINCIPAL = "Memoria!A3:C50"
Const RANGO_MEMORIA_VIRTUAL = "Memoria!E3:G50"
```

---

## 💡 Decisiones de Diseño

### 4.1 Elección de Plataforma: Excel + VBA

**Justificación:**

✅ **Accesibilidad Universal:**

- Excel está disponible en la mayoría de instituciones educativas
- No requiere instalación de software adicional
- Interfaz familiar para usuarios no técnicos

✅ **Visualización Nativa:**

- Celdas como memoria visual
- Colores para estados (activo, inactivo, hazard)
- Shapes para componentes del CPU

✅ **Curva de Aprendizaje Baja:**

- VBA es más simple que C++ o Java
- Sintaxis parecida a Visual Basic
- Debugging integrado con Excel

✅ **Prototipado Rápido:**

- Cambios visuales inmediatos
- No requiere compilación
- Iteración rápida de diseño

**Limitaciones Aceptadas:**

❌ Rendimiento menor que lenguajes compilados
❌ Tamaño máximo del código limitado
❌ No es escalable para simulaciones grandes

### 4.2 Arquitectura Von Neumann

**Justificación:**

✅ **Modelo Educativo Clásico:**

- Enseñado en todos los cursos de arquitectura
- Más simple de entender para principiantes
- Base histórica sólida

✅ **Representación Realista:**

- La mayoría de CPUs x86 son Von Neumann
- Muestra el cuello de botella real del bus
- Refleja limitaciones reales de rendimiento

✅ **Implementación Más Simple:**

- Un solo diccionario para memoria
- Un solo sistema de bus
- Menos complejidad en el código VBA

**Ventaja Didáctica:**

- Estudiantes comprenden por qué existen las cachés
- Entienden el trade-off entre simplicidad y rendimiento
- Aprenden sobre el bottleneck de Von Neumann

### 4.3 Pipeline de 5 Etapas

**Justificación:**

✅ **Estándar RISC:**

- Modelo clásico (IF-ID-EX-MEM-WB)
- Balance entre complejidad y realismo
- Usado en MIPS, ARM básico

✅ **Complejidad Manejable:**

- 5 etapas son suficientes para mostrar conceptos
- No es tan simple como 3 etapas (poco realista)
- No es tan complejo como 10+ etapas (Intel)

✅ **Visualización Clara:**

- Cabe en una tabla de Excel legible
- Cada etapa tiene propósito claro
- Fácil identificar hazards visualmente

### 4.4 Gestión Dinámica de Registros

**Decisión:** Detectar automáticamente qué registros usa el programa.

**Justificación:**

✅ **Reducción de Ruido Visual:**

- No mostrar los 16 registros si solo se usan 3
- Interfaz más limpia y enfocada

✅ **Escalabilidad:**

- Funciona con programas pequeños y grandes
- Se adapta al código del usuario

**Implementación:**

```vba
Sub InicializarSistemaRegistros()
    ' Escanear código en Hoja2
    ' Extraer registros con regex %[a-zA-Z0-9]+
    ' Normalizar a versión 64-bit
    ' Renderizar solo los usados
End Sub
```

### 4.5 Simulación de Memoria con Dictionary

**Decisión:** Usar `Scripting.Dictionary` en lugar de arrays.

**Justificación:**

✅ **Eficiencia O(1):**

- Búsqueda por dirección en tiempo constante
- No importa el tamaño de la memoria

✅ **Memoria Dispersa:**

- No necesita preallocar todo el espacio
- Solo almacena direcciones usadas
- Ahorra memoria de Excel

✅ **Claves String:**

- Fácil depuración (`"MEM_0x1000"`)
- Legible en el debugger

**Implementación:**

```vba
Public memoriaStackGlobal As Object

Sub InicializarMemoria()
    Set memoriaStackGlobal = CreateObject("Scripting.Dictionary")
End Sub

Sub EscribirMemoria(direccion As Long, valor As Long)
    memoriaStackGlobal("MEM_" & direccion) = valor
End Sub
```

### 4.6 Política de Caché LRU

**Decisión:** Implementar Least Recently Used para reemplazo en caché.

**Justificación:**

✅ **Intuitiva:**

- Fácil de explicar a estudiantes
- "Eliminar el menos usado recientemente"

✅ **Efectiva:**

- Buen hit rate en la mayoría de casos
- Explota la localidad temporal

✅ **Simple de Implementar:**

- Mover entradas al final del rango
- Primera celda = más antigua

**Implementación:**

```vba
Sub CargarEnCache(cache As Range, dato As String)
    If CacheLlena(cache) Then
        ' Desplazar todo hacia arriba (elimina primera entrada)
        cache.Cells(1, 1).Delete Shift:=xlUp
    End If
    ' Insertar al final (más reciente)
    cache.Cells(cache.Rows.Count, 1).Value = dato
End Sub
```

### 4.7 Sintaxis AT&T

**Decisión:** Usar sintaxis AT&T en lugar de Intel.

**Justificación:**

✅ **Estándar en Educación:**

- GCC usa AT&T por defecto
- Común en universidades (Linux/Unix)
- Documentación amplia

✅ **Explícito:**

- Tamaños de operando en el opcode (`movl`, `movq`)
- Dirección del dato clara (`src, dest`)

**Comparación:**

```assembly
# AT&T (usado en este simulador)
movl $10, %eax        # Inmediato → Registro
movl %eax, -4(%rbp)   # Registro → Memoria

; Intel (alternativa)
mov eax, 10           ; Inmediato → Registro
mov [rbp-4], eax      ; Registro → Memoria
```

### 4.8 Visualización en Tiempo Real

**Decisión:** Actualizar la interfaz durante la ejecución con pausas.

**Justificación:**

✅ **Efecto Didáctico:**

- Estudiantes ven el flujo de datos
- Comprenden la secuencia temporal
- Identifican visualmente hazards

✅ **Debugging:**

- Facilita encontrar errores
- Ver estado en cada paso

**Implementación:**

```vba
Sub ResaltarTemporal(rango As Range, color As Long, segundos As Double)
    rango.Interior.Color = color
    Application.Wait (Now + TimeValue("0:00:0" & segundos))
    rango.Interior.ColorIndex = xlNone
End Sub
```

---

## 🔧 Componentes Implementados

### 5.1 Listado Completo de Módulos VBA

| Módulo      | Archivo               | Líneas | Funciones Principales                                             |
| ----------- | --------------------- | ------ | ----------------------------------------------------------------- |
| **Módulo1** | Pipeline_Visual.bas   | ~300   | `CrearDiagramaPipeline`, `CrearFlechaForwarding`                  |
| **Módulo2** | Motor_Simulacion.bas  | ~400   | `SimularPipelineCPU`, `DetectarHazard`                            |
| **Módulo3** | Sistema_Registros.bas | ~350   | `LeerRegistro`, `EscribirRegistro`, `InicializarSistemaRegistros` |
| **Módulo4** | ALU_Operaciones.bas   | ~500   | `EjecutarEnALU`, `ActualizarFlags`                                |
| **Módulo5** | Gestion_Memoria.bas   | ~250   | `LeerMemoria`, `EscribirMemoria`, `MostrarMemoriaFormatted`       |
| **Módulo6** | Sistema_Cache.bas     | ~200   | `BuscarEnCache`, `CargarEnCache`                                  |
| **Módulo7** | Unidad_Control.bas    | ~400   | `Fetch`, `Decode`, `Execute`, `MemoryAccess`, `WriteBack`         |
| **Módulo8** | Parser_ATT.bas        | ~300   | `ParsearInstruccionDirecta`, `ParsearOperando`                    |
| **Módulo9** | Utilidades.bas        | ~150   | `ResaltarTemporal`, `LimpiarMemoria`                              |

**Total aproximado:** ~2,850 líneas de código VBA

---

## ⚠️ Manejo de Hazards y Dependencias

### 6.1 Tipos de Hazards

#### 6.1.1 Hazards de Datos (RAW, WAW, WAR)

**RAW (Read After Write) - El Más Común:**

```assembly
movl $10, %eax    # I1: Escribe EAX
addl %eax, %ebx   # I2: Lee EAX antes que I1 complete WB
```

**Detección:**

```vba
Function DetectarHazard(instrActual As InstruccionPipeline, _
                        instrEX As InstruccionPipeline, _
                        instrMEM As InstruccionPipeline) As Boolean
    ' Si instrucción actual lee un registro que
    ' instrucciones anteriores están escribiendo
    If InStr(instrActual.registrosFuente, instrEX.RegistroDestino) > 0 Then
        DetectarHazard = True
    ElseIf InStr(instrActual.registrosFuente, instrMEM.RegistroDestino) > 0 Then
        DetectarHazard = True
    Else
        DetectarHazard = False
    End If
End Function
```

**WAW (Write After Write) - Menos Común:**

```assembly
movl $10, %eax    # I1: Escribe EAX
movl $20, %eax    # I2: También escribe EAX
```

**WAR (Write After Read) - No problemático en pipeline in-order**

### 6.2 Políticas de Mitigación

#### 6.2.1 Stalling (Inserción de Burbujas)

```vba
Sub InsertarStall(instr As InstruccionPipeline, tabla As Range, ciclo As Long)
    Dim numInstr As Long
    numInstr = instr.numeroInstruccion

    ' Marcar como STALL en la tabla
    tabla.Cells(ciclo + 1, numInstr + 1).Value = "STALL"
    tabla.Cells(ciclo + 1, numInstr + 1).Interior.Color = RGB(255, 255, 0)
    tabla.Cells(ciclo + 1, numInstr + 1).Font.Bold = True

    ' La instrucción NO avanza a la siguiente etapa
    ' Se mantiene en ID hasta que el hazard se resuelva
End Sub
```

#### 6.2.2 Forwarding/Bypassing

```vba
Sub CrearFlechaForwarding(ws As Worksheet, x1 As Long, y1 As Long, _
                         x2 As Long, y2 As Long)
    ' Crear línea de forwarding visual
    With ws.Shapes.AddConnector(msoConnectorElbow, x1, y1, x2, y2)
        .Line.ForeColor.RGB = RGB(255, 0, 0)
        .Line.Weight = 2
        .Line.DashStyle = msoLineDash
        .Name = "Forwarding_" & Format(Now, "hhmmss")
    End With
End Sub
```

### 6.3 Visualización de Hazards

**Código de Colores:**

| Color       | Significado                 | RGB                |
| ----------- | --------------------------- | ------------------ |
| 🟡 Amarillo | STALL (hazard detectado)    | RGB(255, 255, 0)   |
| ⚪ Gris     | BUBBLE (ciclo perdido)      | RGB(200, 200, 200) |
| 🔴 Rojo     | Forwarding activo           | RGB(255, 0, 0)     |
| 🟢 Verde    | Instrucción completada (WB) | RGB(144, 238, 144) |
| 🔵 Azul     | Instrucción en ejecución    | RGB(173, 216, 230) |

---

## 📖 Guía de Uso Detallada

### 7.1 Requisitos del Sistema

**Software:**

- Microsoft Excel 2013, 2016, 2019, 2021, o Microsoft 365
- Windows 7/8/10/11
- Macros habilitadas

### 7.2 Instalación

#### 7.2.1 Descargar el Repositorio

```bash
# Opción 1: Clonar con Git
git clone https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86.git
cd Simulador-de-Arquitectura-x86

# Opción 2: Descargar ZIP
# Ir a: https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86
# Clic en "Code" → "Download ZIP"
# Extraer el archivo
```

#### 7.2.2 Abrir Excel

1. Navegar a la carpeta descargada
2. Doble clic en `SimuladorX86.xlsm`
3. Si aparece advertencia de seguridad: Clic en **"Habilitar contenido"**

#### 7.2.3 Habilitar Macros (si no aparece automáticamente)

```
Archivo → Opciones → Centro de confianza
→ Configuración del Centro de confianza
→ Configuración de macros
→ Seleccionar "Habilitar todas las macros"
```

⚠️ **Nota de Seguridad:** Solo habilitar macros de fuentes confiables.

#### 7.2.4 Verificar Instalación

Presionar `Alt + F11` para abrir el editor VBA:

```
✓ VBAProject (SimuladorX86.xlsm)
  ├─ Microsoft Excel Objects
  │   ├─ Hoja1 (Entrada)
  │   ├─ Hoja2 (Simulador)
  │   └─ ThisWorkbook
  └─ Módulos
      ├─ Módulo1
      ├─ Módulo2
      ├─ Módulo3
      ├─ Módulo4
      ├─ Módulo5
      ├─ Módulo6
      ├─ Módulo7
      ├─ Módulo8
      └─ Módulo9
```

### 7.3 Uso Básico

#### 7.3.1 Cargar Código Ensamblador

1. Ir a **Hoja1**
2. En la celda **B3**, escribir código ensamblador:

```assembly
pushq %rbp
movq %rsp, %rbp
movl $9, -4(%rbp)
movl $11, -8(%rbp)
movl -4(%rbp), %edx
movl -8(%rbp), %eax
addl %edx, %eax
movl %eax, -12(%rbp)
leave
ret
```

3. Clic en el botón **"Cargar Ensamblador"**
4. Esperar mensaje: "Código cargado exitosamente"

#### 7.3.2 Ejecutar Paso a Paso

1. Ir a **Hoja2**
2. Clic en botón **"Avanzar Ciclo"**
3. Observar:

   - PC incrementándose
   - IR con la instrucción actual
   - Registros actualizándose
   - Memoria cambiando

4. Continuar haciendo clic hasta finalizar

#### 7.3.3 Simular Pipeline Completo

1. En **Hoja2**, clic en **"Simular Pipeline"**
2. Ver tabla automática ciclo-a-ciclo:

```
Ciclo │ I1  │ I2  │ I3  │ I4  │ I5
──────┼─────┼─────┼─────┼─────┼─────
  1   │ IF  │     │     │     │
  2   │ ID  │ IF  │     │     │
  3   │ EX  │ ID  │ IF  │     │
  ...
```

3. Observar colores indicando STALLs
4. Ver mensaje final con estadísticas

#### 7.3.4 Visualizar Memoria

1. Clic en botón **"Ver Memoria"**
2. Se abre hoja "Memoria" con tabla:

```
┌─────────────┬──────────┬──────────┐
│ Dirección   │ Hex      │ Decimal  │
├─────────────┼──────────┼──────────┤
│ 0x7FFFFF00  │ 0x09     │ 9        │
│ 0x7FFFFF04  │ 0x0B     │ 11       │
│ 0x7FFFFF08  │ 0x14     │ 20       │
└─────────────┴──────────┴──────────┘
```

#### 7.3.5 Inspeccionar Registros

Los registros se actualizan automáticamente en **Hoja2** (columnas F-H):

```
┌──────────┬─────────────┬──────────┐
│ Registro │ Valor (Hex) │ Decimal  │
├──────────┼─────────────┼──────────┤
│ RAX      │ 0x00000014  │ 20       │
│ RBX      │ 0x00000000  │ 0        │
│ RDX      │ 0x00000009  │ 9        │
│ RBP      │ 0x7FFFFF00  │ ...      │
│ RSP      │ 0x7FFFFEF8  │ ...      │
└──────────┴─────────────┴──────────┘
```

### 7.4 Funciones Avanzadas

#### 7.4.1 Resetear Simulador

```vba
Sub ResetearSimulador()
    ' Presionar Alt + F8 → Seleccionar ResetearSimulador → Ejecutar

    ' O agregar botón en Hoja2
End Sub
```

#### 7.4.2 Configurar Velocidad de Simulación

Editar en VBA (Alt + F11):

```vba
' Buscar en Módulo7:
Application.Wait (Now + TimeValue("0:00:00.5"))
'                                        ^^^
'                                        Cambiar a 0.1 para más rápido
'                                        Cambiar a 2.0 para más lento
```

#### 7.4.3 Exportar Resultados

```vba
Sub ExportarMemoria()
    ' Guardar contenido de memoria en archivo de texto
    Dim fso As Object, archivo As Object
    Set fso = CreateObject("Scripting.FileSystemObject")
    Set archivo = fso.CreateTextFile("memoria_" & Format(Now, "yyyymmdd_hhmmss") & ".txt", True)

    Dim clave As Variant
    For Each clave In memoriaStackGlobal.Keys
        archivo.WriteLine clave & " = " & memoriaStackGlobal(clave)
    Next

    archivo.Close
    MsgBox "Memoria exportada", vbInformation
End Sub
```

### 7.5 Solución de Problemas

#### 7.5.1 Errores Comunes

**Error: "Variable no definida"**

- **Causa:** Falta `Option Explicit` o variable no declarada
- **Solución:** Verificar que `memoriaStackGlobal` y `registrosDict` estén inicializados

**Error: "El objeto no admite esta propiedad o método"**

- **Causa:** Objeto no creado correctamente
- **Solución:**

```vba
Set memoriaStackGlobal = CreateObject("Scripting.Dictionary")
Set registrosDict = CreateObject("Scripting.Dictionary")
```

**Error: "Índice fuera del intervalo"**

- **Causa:** Acceso a celda inexistente
- **Solución:** Verificar rangos nombrados existen

#### 7.5.2 Debugging

Presionar `Alt + F11` → `Ver` → `Ventana Inmediato` (Ctrl+G):

```vba
' Comandos útiles en ventana inmediato:
? PC                                  ' Ver valor de PC
? memoriaStackGlobal.Count            ' Cantidad de direcciones en memoria
? registrosDict("RAX")                ' Valor de RAX
? Range("CELDA_PC").Value             ' Valor en celda PC
```

---

## 💻 Ejemplos Prácticos

### 8.1 Ejemplo Completo: Suma de Dos Números

```assembly
# main.s - Suma dos números y guarda el resultado

pushq %rbp              # Guardar base pointer
movq %rsp, %rbp         # Establecer nuevo frame
subq $16, %rsp          # Reservar espacio en stack

# Inicializar variables
movl $9, -4(%rbp)       # a = 9
movl $11, -8(%rbp)      # b = 11

# Cargar a registros
movl -4(%rbp), %edx     # EDX = a
movl -8(%rbp), %eax     # EAX = b

# Sumar
addl %edx, %eax         # EAX = EAX + EDX (resultado = 20)

# Guardar resultado
movl %eax, -12(%rbp)    # resultado = EAX

# Limpiar y retornar
movl $0, %eax           # return 0
leave                   # Restaurar stack
ret                     # Retornar
```

**Ejecución Paso a Paso:**

```
Ciclo 1: pushq %rbp
  IF: Leer instrucción
  ID: Identificar PUSH
  EX: RSP = RSP - 8
  MEM: Escribir RBP en [RSP]
  WB: Actualizar RSP

Ciclo 2: movq %rsp, %rbp
  IF: Leer instrucción
  ID: Identificar MOV
  EX: Copiar RSP
  MEM: -
  WB: RBP = RSP

... (continúa para cada instrucción)
```

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
│   3   │ EX  │ ID  │     │ ← I2 detecta hazard
│   4   │ MEM │STALL│ IF  │ ← I2 espera
│   5   │ WB  │STALL│ ID  │ ← I2 espera
│   6   │     │ EX  │ ID  │ ← I2 puede continuar
│   7   │     │ MEM │ EX  │
│   8   │     │ WB  │ MEM │
│   9   │     │     │ WB  │
└───────┴─────┴─────┴─────┘
Total: 9 ciclos, 2 ciclos perdidos por hazard

Pipeline con Forwarding:
┌───────┬─────┬─────┬─────┐
│ Ciclo │ I1  │ I2  │ I3  │
├───────┼─────┼─────┼─────┤
│   1   │ IF  │     │     │
│   2   │ ID  │ IF  │     │
│   3   │ EX  │ ID  │     │
│   4   │ MEM │ EX  │ IF  │ ← Forwarding EX→EX
│   5   │ WB  │ MEM │ ID  │
│   6   │     │ WB  │ EX  │
│   7   │     │     │ MEM │
│   8   │     │     │ WB  │
└───────┴─────┴─────┴─────┘
Total: 8 ciclos, 1 ciclo ahorrado
```

---

## 📊 Desarrollo del Proyecto

### 9.1 Cronología de Desarrollo

**Total: 6 días (29 sept - 5 oct 2024)**

- Día 1: Componentes básicos (CPU, ALU, Memoria)
- Días 2-3: Pipeline y caché
- Días 4-5: Optimización y hazards
- Día 6: Testing y documentación

### 9.2 Equipo de Desarrollo

| Desarrollador                  | Rol Principal       | Issues Completadas |
| ------------------------------ | ------------------- | ------------------ |
| **Alejandro Ramírez Vallejos** | Arquitectura y Core | 11                 |
| **Josue Galo Balbontin**       | Interfaz y Parser   | 10                 |
| **Fernando Terrazas**          | Memoria y Pipeline  | 10                 |

---

## 📚 Referencias y Recursos

### 11.1 Literatura Académica

1. Patterson, D. A., & Hennessy, J. L. (2017). _Computer Organization and Design_ (5th ed.). Morgan Kaufmann.
2. Stallings, W. (2015). _Computer Organization and Architecture_ (10th ed.). Pearson.
3. Tanenbaum, A. S., & Austin, T. (2013). _Structured Computer Organization_ (6th ed.). Pearson.

### 11.2 Recursos en Línea

- [Intel Manual](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
- [AT&T Syntax](https://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax)
- [Pipeline Tutorial](https://www.scss.tcd.ie/~jones/CS2011/pipeline.html)

---

## 📄 Licencia y Autores

### 12.1 Licencia

**Uso Educativo Libre** - Este simulador puede ser usado libremente con fines educativos.

### 12.2 Autores

- **Alejandro Ramírez Vallejos** - [@alejandroramirezvallejos](https://github.com/alejandroramirezvallejos)
- **Josue Galo Balbontin Ugarteche** - [@josue-balbontin](https://github.com/josue-balbontin)
- **Fernando Terrazas Llanos** - [@FernandoTerrazasLl](https://github.com/FernandoTerrazasLl)

### 12.3 Repositorio

📂 **GitHub:** [Simulador-de-Arquitectura-x86](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)

---
