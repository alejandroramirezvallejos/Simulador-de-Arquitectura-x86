# Documentación del Backlog y Roadmap del Proyecto
## Simulador de Arquitectura x86

---

## 📋 Resumen Ejecutivo

Este documento presenta una documentación exhaustiva del Backlog y Roadmap del proyecto **Simulador de Arquitectura x86**, basado en el análisis del proyecto Kanban y las issues registradas en GitHub. El proyecto fue desarrollado en un período de 6 días (del 29 de septiembre al 5 de octubre de 2025) con la participación de 3 desarrolladores principales.

---

## 👥 Equipo de Desarrollo

| Desarrollador | Usuario GitHub | Rol Principal |
|---------------|----------------|---------------|
| Alejandro Ramírez | @alejandroramirezvallejos | Líder de Proyecto / Backend |
| Josué Balbontín | @josue-balbontin | Desarrollador Backend / Integración |
| Fernando Terrazas | @FernandoTerrazasLl | Desarrollador Backend / UI |

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

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #1 | Implementar CPU Base con Registros y Banderas | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |
| #2 | Desarrollar Unidad Aritmético-Lógica (ALU) | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |
| #3 | Implementar Sistema de Memoria RAM | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |

**Entregables:**
- Sistema de registros x86 funcional
- ALU con operaciones aritméticas básicas
- Sistema de memoria RAM básico

---

#### **Sprint 1.2: Parser y Motor de Simulación**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #4 | Crear Parser de Ensamblador x86 | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |
| #5 | Desarrollar Motor de Simulación | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |

**Entregables:**
- Parser de instrucciones ensamblador x86
- Motor de ejecución de instrucciones

---

#### **Sprint 1.3: API y Sistema de Salida**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #6 | Desarrollar API para VBA Excel | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |
| #7 | Implementar Sistema de Salida JSON | @alejandroramirezvallejos | ✅ Cerrado | Alta | 29/09 | 29/09 |
| #8 | Configurar Sistema de Tipos | @alejandroramirezvallejos | ✅ Cerrado | Media | 29/09 | 29/09 |

**Entregables:**
- API DLL para integración con VBA
- Sistema de serialización JSON
- Sistema de tipos de datos

---

### **Fase 2: Interfaz y Características Avanzadas (Días 2-3)**

#### **Sprint 2.1: Interfaz Visual y Generación de Código**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #9 | Desarrollar Interfaz Visual Excel VBA | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Alta | 29/09 | 03/10 |
| #10 | Implementar Generador C++ a Ensamblador AT&T | @josue-balbontin, @alejandroramirezvallejos | ✅ Cerrado | Media | 29/09 | 02/10 |

**Entregables:**
- Interfaz gráfica en Excel con VBA
- Generador automático de código ensamblador

---

#### **Sprint 2.2: Sistemas de Memoria Avanzados**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #11 | Desarrollar Sistema de Memoria Caché con LRU | @alejandroramirezvallejos, @FernandoTerrazasLl | ✅ Cerrado | Alta | 29/09 | 01/10 |
| #12 | Implementar Pipeline de CPU (4 Etapas) | @FernandoTerrazasLl | ✅ Cerrado | Alta | 29/09 | 01/10 |
| #13 | Desarrollar Sistema de Entrada/Salida (I/O) | @FernandoTerrazasLl | ✅ Cerrado | Media | 29/09 | 03/10 |
| #14 | Implementar Memoria Virtual Básica | @FernandoTerrazasLl | ✅ Cerrado | Media | 29/09 | 01/10 |

**Entregables:**
- Sistema de caché L1/L2 con política LRU
- Pipeline de CPU de 4 etapas
- Sistema básico de I/O
- Memoria virtual con paginación

---

### **Fase 3: Integración y Optimización (Días 4-5)**

#### **Sprint 3.1: Integración Excel-C++**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #15 | Conectar Excel con simulador C++ mediante DLL | @josue-balbontin | ✅ Cerrado | Crítica | 30/09 | 30/09 |
| #16 | Localización automática del DLL | @josue-balbontin | ✅ Cerrado | Media | 30/09 | 30/09 |

**Entregables:**
- Integración completa Excel-DLL
- Carga automática de DLL

---

#### **Sprint 3.2: Documentación y Mejoras**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #18 | Documentar relaciones del ciclo de instrucción | @josue-balbontin | ✅ Cerrado | Baja | 30/09 | 30/09 |
| #19 | Automatizar gestión de memoria RAM/virtual | @josue-balbontin | ✅ Cerrado | Media | 30/09 | 30/09 |

**Entregables:**
- Documentación técnica del ciclo de instrucciones
- Mejora en la gestión de memoria

---

### **Fase 4: Características Avanzadas (Días 5-6)**

#### **Sprint 4.1: Visualización de Memoria**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #20 | Desarrollar interfaz para Memoria RAM/Virtual | @FernandoTerrazasLl | ✅ Cerrado | Media | 30/09 | 01/10 |
| #21 | Comparativa Von Neumann y Harvard | @FernandoTerrazasLl | ✅ Cerrado | Alta | 30/09 | 01/10 |

**Entregables:**
- Visualización avanzada de RAM/Memoria Virtual
- Comparación visual de arquitecturas

---

#### **Sprint 4.2: Ejecución de Código**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #22 | Ejecución de código ensamblador en DLL C++ | @josue-balbontin | ✅ Cerrado | Crítica | 01/10 | 02/10 |

**Entregables:**
- Sistema de ejecución de código ensamblador
- Sistema de debugging
- Mejoras en el formato JSON

---

### **Fase 5: Refinamiento Final (Días 6-7)**

#### **Sprint 5.1: Optimizaciones Finales**

| # | Título | Asignado a | Estado | Prioridad | Inicio | Cierre |
|---|--------|------------|--------|-----------|--------|--------|
| #24 | Gestión dinámica registros x86-64 | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Alta | 03/10 | 03/10 |
| #25 | Visualización pipeline paso a paso | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Alta | 03/10 | 03/10 |
| #26 | Caché mejorada con política LRU | @FernandoTerrazasLl | ✅ Cerrado | Alta | 03/10 | 03/10 |
| #27 | Instrucciones aritméticas (MOV, ADD, SUB, MUL, DIV, PUSH, POP) | @josue-balbontin, @FernandoTerrazasLl | ✅ Cerrado | Crítica | 03/10 | 03/10 |

**Entregables:**
- Sistema de registros dinámicos x86-64
- Visualización mejorada del pipeline
- Caché optimizada con LRU
- Conjunto completo de instrucciones aritméticas

---

## 📈 Análisis de Distribución de Trabajo

### Por Desarrollador

| Desarrollador | Issues Asignadas | Issues Individuales | Issues en Colaboración |
|---------------|------------------|---------------------|------------------------|
| @alejandroramirezvallejos | 11 | 9 | 2 |
| @josue-balbontin | 10 | 5 | 5 |
| @FernandoTerrazasLl | 10 | 5 | 5 |

### Por Tipo de Tarea

| Categoría | Cantidad | Porcentaje |
|-----------|----------|------------|
| Backend/Core | 14 | 51.9% |
| Interfaz/UI | 5 | 18.5% |
| Integración | 4 | 14.8% |
| Documentación | 2 | 7.4% |
| Pull Requests | 2 | 7.4% |

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

## 🔗 Enlaces Útiles

- **Repositorio:** [alejandroramirezvallejos/Simulador-de-Arquitectura-x86](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86)
- **Issues:** [Lista completa de Issues](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86/issues)
- **Pull Requests:** [Lista de PRs](https://github.com/alejandroramirezvallejos/Simulador-de-Arquitectura-x86/pulls)

---

**Documento generado el:** 5 de Octubre de 2025  
**Versión:** 1.0  
**Estado del Proyecto:** ✅ Completado