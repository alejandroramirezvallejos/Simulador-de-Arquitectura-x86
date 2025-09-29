# 👷🏻‍♀️Simulador-de-Arquitectura-x86

El objetivo de este proyecto es crear un simulador interactivo de arquitectura x86. Esta herramienta educativa permite visualizar y comprender el funcionamiento de los principales componentes de una computadora, facilitando el aprendizaje de la arquitectura x86.

# 🖥️ Estado Actual del Proyecto

## ✅ **COMPONENTES IMPLEMENTADOS**

### 1. 🧠 **CPU Básico** 
**Archivos:** `src/cpu.hpp`, `src/cpu.cpp`
- **8 registros:** EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI
- **Contador de programa:** seguimiento de instrucciones 
- **3 banderas:** CERO, ACARREO, SIGNO (eliminada DESBORDAMIENTO por no usarse)
- **Tipos modernos:** enum class con type safety

### 2. 🔢 **ALU (Unidad Aritmético-Lógica)**
**Archivos:** `src/alu.hpp`, `src/alu.cpp`
- **Operaciones básicas:** suma y resta únicamente
- **Comparación** entre números
- **Actualización automática** de 3 banderas (CERO, ACARREO, SIGNO)
- **Sin overflow detection** (simplificado intencionalmente)

### 3. 💾 **Sistema de Memoria RAM**
**Archivos:** `src/memoria.hpp`, `src/memoria.cpp`
- **1 KB de RAM** (1024 bytes total = 256 números de 32-bit)
- **Operaciones:** `leer_numero()`, `escribir_numero()`, `leer_byte()`, `escribir_byte()`
- **Formato little-endian** (compatible con x86)
- **Protección básica:** validación de rangos

### 4. 📝 **Parser de Ensamblador**
**Archivos:** `src/parser.hpp`, `src/parser.cpp`
- **6 instrucciones:** MOV, ADD, SUB, JMP, LOAD, STORE
- **Sintaxis Intel:** `MOV destino, origen`
- **Valores inmediatos:** `MOV EAX, 10`
- **Entre registros:** `ADD EAX, EBX`
- **Acceso memoria:** `LOAD EAX, 100`
- **Funciones auxiliares:** eliminación de código duplicado

### 5. ⚙️ **Motor de Simulación**
**Archivos:** `src/motor_simulacion.hpp`, `src/motor_simulacion.cpp`
- **Ejecución paso a paso:** función `siguiente_paso()`
- **Control de flujo:** saltos JMP
- **Gestión de estado:** carga, ejecución, reinicio
- **Arquitectura modular:** métodos especializados por instrucción

### 6. 🔌 **API DLL para Excel**
**Archivos:** `main.cpp` (sección `extern "C"`)
- **6 funciones exportadas:** inicializar, cargar, ejecutar, estado, reiniciar, finalizar
- **Gestión de memoria:** puntero global con delete/nullptr
- **Compatibilidad VBA:** tipos C compatibles

### 7. 📊 **Serialización JSON**
**Archivos:** `src/salida_json.cpp`, `include/salida_json.hpp`
- **Estado completo:** registros, contador, banderas
- **Memoria completa:** 256 números 
- **Formato legible:** true/false para banderas

### 8. 🧪 **Sistema de Pruebas**
**Archivos:** `main.cpp` (función `main()`)
- **Solo para testing** durante desarrollo
- **No se usa en producción** (Excel será la interfaz)
- **Programa de ejemplo:** MOV, ADD, SUB para verificación

---

## ❌ **COMPONENTES FALTANTES (REQUERIMIENTOS OBLIGATORIOS)**

### 1. 📱 **Interfaz Excel VBA** ⚠️ CRÍTICO
**Estado:** NO IMPLEMENTADO
**Requerimiento:** OBLIGATORIO para entrega
**Impacto:** Sin esto no se puede presentar el proyecto

**Falta implementar:**
- Interfaz gráfica en Excel
- Formularios VBA de control
- Visualización de registros/memoria en celdas
- Parser JSON en VBA
- Carga de archivos desde Excel

### 2. 🗂️ **Memoria Caché** ⚠️ OBLIGATORIO
**Estado:** NO IMPLEMENTADO
**Requerimiento:** "Visualizar la Memoria Cache"
**Impacto:** Requisito específico del proyecto

**Falta implementar:**
- Caché de datos/instrucciones
- Política LRU (Least Recently Used)
- Estadísticas hit/miss
- Simulación de velocidades diferentes

### 3. 🔄 **Pipeline de CPU** ⚠️ OBLIGATORIO
**Estado:** NO IMPLEMENTADO  
**Requerimiento:** "simular y mostrar el flujo de las instrucciones a través del pipeline"
**Impacto:** Requisito específico del proyecto

**Falta implementar:**
- 4 etapas: FETCH → DECODE → EXECUTE → WRITE-BACK
- Detección de hazards/riesgos
- Visualización del flujo
- Manejo de stalls

### 4. 📤📥 **Sistema I/O** ⚠️ OBLIGATORIO
**Estado:** NO IMPLEMENTADO
**Requerimiento:** "Unidad de Entrada/Salida (I/O)"
**Impacto:** Requisito específico del proyecto

**Falta implementar:**
- Instrucciones IN/OUT
- Simulación de dispositivos
- Buffer de entrada/salida
- Interrupciones básicas

### 5. 🌐 **Memoria Virtual** ⚠️ OBLIGATORIO
**Estado:** NO IMPLEMENTADO
**Requerimiento:** "Visualizar la Memoria Virtual"
**Impacto:** Requisito específico del proyecto

**Falta implementar:**
- Traducción direcciones virtuales → físicas
- Tabla de páginas
- Simulación de page faults
- TLB básico

### 6. 🔄 **Generador C++ → ASM** 💰 BONUS
**Estado:** PLANIFICADO
**Requerimiento:** OPCIONAL pero valorado
**Herramienta:** `g++ -S programa.cpp -o programa.s`

**Pipeline planeado:** C++ → ASM AT&T → Parser → Simulación

---

## 📊 **ANÁLISIS REAL DEL ESTADO**

### ✅ **COMPLETADO:** 
**Lo que funciona:**
- Núcleo básico del simulador x86
- Parser de 6 instrucciones básicas
- API lista para Excel

### ❌ **PENDIENTE:** 
**Crítico para entrega:**
- Interfaz Excel (sin esto no hay proyecto)
- 4 componentes obligatorios (Caché, Pipeline, I/O, Virtual Memory)
- Documentación formal

### ⚠️ **SITUACIÓN ACTUAL:**
- **Base sólida:** El núcleo funciona correctamente
- **Trabajo intenso pendiente:** La mayoría de requerimientos específicos no están implementados
- **Riesgo:** Sin las características obligatorias, el proyecto no cumple los requisitos mínimos

---

## 🎯 **PLAN DE ACCIÓN URGENTE**

### **URGENTE**
1. **Crear interfaz Excel completa** - Sin esto no hay entrega
2. **Implementar pipeline básico** - Requerimiento obligatorio

### **PROXIMAMENTE**
1. **Memoria caché con LRU** - Requerimiento obligatorio
2. **Sistema I/O básico** - Requerimiento obligatorio  
3. **Memoria virtual básica** - Requerimiento obligatorio

### **SI HAY TIEMPO:**
1. **Generador C++ → ASM AT&T** - Puntos extra
2. **Documentación APA** - Presentación profesional

---

## 🛠️ **INSTRUCCIONES DE COMPILACIÓN**

### **Para DLL (Excel):**
```bash
g++ -shared -o simulador.dll main.cpp src/parser.cpp src/cpu.cpp src/alu.cpp src/memoria.cpp src/motor_simulacion.cpp src/salida_json.cpp -std=c++20
```

### **Para testing (consola):**
```bash
g++ -o simulador.exe main.cpp src/parser.cpp src/cpu.cpp src/alu.cpp src/memoria.cpp src/motor_simulacion.cpp src/salida_json.cpp -std=c++20
```

---

## 💡 **CONCLUSIÓN**

**🟡 ESTADO ACTUAL:** El proyecto tiene una base técnica sólida pero le faltan la mayoría de las características requeridas por el enunciado.

**🚨 RIESGO:** Sin implementar las características obligatorias (Caché, Pipeline, I/O, Memoria Virtual, Interfaz Excel), el proyecto no cumplirá con los requisitos mínimos para aprobación.

**🎯 RECOMENDACIÓN:** Enfocar todos los esfuerzos en implementar primero la interfaz Excel y luego las características obligatorias, dejando las opcionales para el final.
