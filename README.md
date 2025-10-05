# Simulador de Arquitectura x86

## Objetivo

El objetivo de este proyecto es crear un simulador interactivo de arquitectura x86. Esta herramienta educativa permite visualizar y comprender el funcionamiento de los principales componentes de una computadora, facilitando el aprendizaje de la arquitectura x86.

## Índice

1. Resumen
2. Alcance y supuestos
3. Arquitectura global (visión de alto nivel)
4. Componentes: descripción funcional por bloques

   - 4.1 Unidad de Control
   - 4.2 Pipeline (IF, ID, EX, MEM, WB)
   - 4.3 Buffers (Fetch / Decode)
   - 4.4 Unidad Aritmético-Lógica (ALU) — estructura y comportamiento
   - 4.5 Banco de registros (Registro State Manager)
   - 4.6 Subsistema de memoria y MMU
   - 4.7 Cachés (I-Cache, D-Cache, L2, L3) y políticas básicas
   - 4.8 Interfaz Registro↔Memoria (Selector / RIM / RDM)
   - 4.9 Visualización (shapes, rangos y convenciones en Excel)

5. Flujo de datos y control (end-to-end)
6. Parsing y representación de instrucciones (AT&T)
7. Simulación del pipeline: algoritmo y reglas
8. Manejo de hazards: RAW, load-use, forwarding y stalls
9. Ejemplos prácticos y tablas ciclo-a-ciclo

   - 9.1 Programa `main` (capturado) — ASM y análisis
   - 9.2 Tabla ciclo-a-ciclo detallada (dos políticas: sin forwarding y con forwarding)
   - 9.3 Ejemplo push/pop y acceso a stack (paso a paso)
   - 9.4 Ejemplo de store/load que no generan dependencia (direcciones distintas)

10. Anexo: resumen de funciones VBA

---

## 1. Resumen ejecutivo

Este documento describe un simulador de arquitectura x86 implementado en Excel con macros VBA. Está orientado a enseñanza y experimentación: permite cargar código ensamblador en sintaxis AT&T, ver cómo las instrucciones avanzan por un pipeline de 5 etapas, observar estados de caché y memoria, y visualizar cómo se leen/escriben registros y memoria.

La implementación original incluye: parsing de instrucciones, gestor dinámico de registros, memoria simulada con `Scripting.Dictionary`, implementación de la ALU y rutinas por instrucción (MOV, ADD, SUB, PUSH, POP, etc.), una tabla tipo pipeline y una interfaz visual con shapes y colores.

---

## 2. Alcance y supuestos

- **Lenguaje de entrada:** ensamblador AT&T (ej.: `movl $9, -4(%rbp)` , `addl %edx, %eax`).
- **Pipeline modelado:** 5 etapas (IF, ID, EX, MEM, WB).
- **Memoria:** simulada con un diccionario en VBA (`memoriaStackGlobal`), y visualización en celdas que representan RAM, caches, buffers.
- **Registros:** normalizados a nombres 64-bit (RAX, RBX, ... R15) mediante la función de normalización del código original.

---

## 3. Arquitectura

En el diagrama lógico (representado con shapes en la hoja), se distinguen tres zonas principales:

1. **Unidad de Control** — genera el ciclo de reloj lógico, secuencia fetch/decode, y controla los buffers e I-cache.
2. **Pipeline y ALU** — etapas IF/ID/EX/MEM/WB y la ALU/arreglo de ejecución con sus registros y flags.
3. **Memoria y Caches** — I-cache, D-cache, memoria principal (RAM visual) y respaldo (HDD/virtual), más una MMU/selector conceptual.

Los datos fluyen desde la memoria/entrada al IF, se decodifican, se ejecutan en la ALU (posible acceso a memoria) y, finalmente, se escriben en el banco de registros. En paralelo, la visualización muestra estados de buffers, caches y registros.

---

## 4. Componentes: descripción funcional por bloques

Cada bloque contiene: responsabilidad, subcomponentes, entradas/salidas, cómo interactúa con otros bloques y notas de implementación específicas basadas en el código VBA provisto.

### 4.1 Unidad de Control

**Responsabilidad:** gestionar el flujo de instrucciones (PC), coordinar accesos a I-cache, alimentar buffers y activar etapas del pipeline.

**Subcomponentes y variables visibles:**

- `PC` (valor de programa, variable pública en VBA).
- Shapes: `CELDA_PC`, `CELDA_MAR`, `CELDA_MDR` (marcos visuales para PC/MAR/MDR).
- Funciones relacionadas: `Fetch`, `Decode`.

**Entradas:** dirección PC, contenido de memoria (programa en hoja), estado de I-cache.
**Salidas:** instrucción cargada en `IR` (shape `CELDA_IR`), contenido en buffers.

**Interacción:**

- En `Fetch`, se llama a `BuscarEnCache(RANGO_I_CACHE, filaActual, instruccion)`. En caso de miss, la unidad de control ordena `CargarEnCache` desde memoria principal.
- Posteriormente, la unidad de control pasa la instrucción al buffer de decode y enciende decodificador (procedimiento `Decode`).

**Notas:**

- El `Fetch` actualiza shapes y resalta celdas; utiliza `Application.Wait` y `ResaltarTemporal` para efectos visuales.

---

### 4.2 Pipeline (IF, ID, EX, MEM, WB)

**Responsabilidad:** permitir ejecución superpuesta de instrucciones mediante etapas definidas.

**Estructura en código:** `Type InstruccionPipeline` (campo `instruccion`, `etapa`, `RegistroDestino`, `registrosFuente`, `ciclo`) y array `pipeline(1 To 5)` en `SimularPipelineCPU`.

**Operación (por ciclo):**

- Se procesa WB→MEM→EX→ID→IF en ese orden para desplazar instrucciones hacia adelante correctamente.
- En ID se detectan hazards y, si aparecen, se insertan `STALL` y `BUBBLE` (tabla visual) y se evita `IF` ese ciclo.

**Entradas/salidas:**

- IF toma una instrucción desde `instrucciones()` (array) y la coloca en pipeline(1).
- WB escribe en la tabla de resultados (rango pipeline) o invoca `EscribirRegistro` en la ejecución paso a paso.

---

### 4.3 Buffers (Fetch / Decode)

**Función:** reflejar la latencia entre etapas y servir de almacenamiento temporal durante stalls.

**Implementación:** rangos en hoja (`RANGO_FETCH_BUFFER`, `RANGO_DECODE_BUFFER`) y funciones `CargarEnBuffer`, `LimpiarBuffer`.

**Interacción:**

- `Fetch` pone la instrucción en `RANGO_FETCH_BUFFER`; `Decode` toma de `RANGO_DECODE_BUFFER`.

---

### 4.4 Unidad Aritmético-Lógica (ALU)

**Responsabilidad:** realizar operaciones aritméticas y lógicas (ADD, SUB, MUL, DIV), manejar movs, push/pop, y preparar resultados para writeback o memoria.

**Subcomponentes (conceptuales/visual):**

- Entradas: `RANGE_ALU_INPUT1`, `RANGE_ALU_INPUT2` (celdas en la hoja).
- Salida: `RANGE_ALU_OUTPUT` (Z1).
- Estado visual: `EstadoALU` shape (indica operación en curso).

**Procedimientos clave (VBA original):**

- `EjecutarEnALU(Operacion)`: lee `CELDA_IR`, parsea con `ParsearInstruccionDirecta`, obtiene operandos con `ObtenerValorOperando`, ejecuta la operación y escribe resultado en `Z1/Z2` o en memoria si destino es memoria.
- `ActualizarFlags(resultado)`: calcula ZF, SF, CF, OF y actualiza `Flags` shape.

**Comportamiento paso a paso:**

1. `Execute` invoca `EjecutarEnALU` para instrucciones aritméticas.
2. `ParsearInstruccionDirecta` separa opcode y operandos y normaliza registro destino.
3. `ObtenerValorOperando` devuelve número según tipo (`inmediato`, `registro`, `memoria`).
4. Resultado: si destino es registro se escribe en `Z1`/`Z2` (esquema de staging para WB). Si destino es memoria, `EscribirMemoria` actualiza `memoriaStackGlobal`.

**Notas:**

- `EjecutarMOVSS` maneja instrucciones de punto flotante con simplificación (escribe valor simulado en memoria si aplica).
- Las operaciones de división evitan división por cero y usan división entera `\`.

---

### 4.5 Registro State Manager

**Responsabilidad:** detectar registros usados por el programa, almacenar valores, exponer API `LeerRegistro`/`EscribirRegistro` y renderizar la UI.

**Algoritmo de inicialización:**

- `InicializarSistemaRegistros` escanea las instrucciones de la hoja (fila 3 a 10000 en el código original), extrae tokens `%reg` con `ExtraerRegistrosDeInstruccion`, normaliza nombres (`NormalizarNombreRegistro`) y crea arrays `registrosNombres(1..N)` y `registrosValores(1..N)`.
- Asegura la presencia de los registros básicos RAX..R15.

**Funciones públicas usadas por otras partes:**

- `LeerRegistro(nombreReg As String) As Long` — devuelve valor; si no existe, crea nuevo registro dinámico y lo renderiza.
- `EscribirRegistro(nombreReg As String, valor As Long)` — escritura y actualización visual.
- `ResaltarRegistro(nombreReg, color)` — colorea celda de registro cuando se lee/escribe.

**Notas:**

- `RenderizarRegistrosEnExcel` escribe los pares nombre/valor en columnas, ajusta ancho y aplica color y bordes.

---

### 4.6 Subsistema de memoria y MMU

**Responsabilidad:** proveer almacenamiento para variables (stack, datos), simular lectura/escritura y colaborar con cachés.

**Implementación:**

- `memoriaStackGlobal` (Dictionary) guarda claves `"MEM_<direccion>"` con valores.
- `LeerMemoria(expresion)` y `EscribirMemoria(expresion, valor)` calculan `direccionReal = LeerRegistro(regBase) + offset` y leen/escriben en `memoriaStackGlobal`.
- `MostrarMemoriaFormatted` imprime la memoria ordenada por dirección.

**Interacción con cache:** `MemoryAccess` consulta D-cache antes de acceder a `memoriaStackGlobal`.

---

### 4.7 Cachés (I-Cache, D-Cache, L2, L3) y políticas básicas

**Representación:** rangos en hoja (`RANGO_I_CACHE`, `RANGO_D_CACHE`) que contienen entradas con formato `Addr:<PC> | <direccion>=<valor>`.

**Funciones:**

- `BuscarEnCache(cache, direccion, dato)` — compara texto en celdas para detectar `Addr:`.
- `CargarEnCache(cache, dato)` — actualiza entrada si existe; si no, añade en primera celda vacía; si está lleno, desplaza las entradas (LRU simple).
- `CargarEnCacheAcumulativo` — similar, pero mantiene `direccion=valor` y actualiza si la dirección ya existe.

**Política LRU simple:** si el cache está lleno se desplazan las entradas hacia arriba y se coloca la nueva al final.

**Efecto en la simulación:**

- `Fetch` usa I-cache; `MemoryAccess` usa D-cache.

---

### 4.8 Interfaz Registro↔Memoria (Selector / RIM / RDM)

**Responsabilidad:** coordinar la lectura/escritura entre registros y memoria; seleccionar la fuente correcta para operandos.

**Implementación:**

- `ObtenerValorOperando(tipo, valor)` actúa como selector: si `tipo="registro"` → `LeerRegistro`, si `tipo="memoria"` → `LeerMemoria`, si `inmediato` → devuelve valor.

**Nota:** el diagrama conceptual contiene bloques `RIM`/`RDM` que apuntan de caches/registros a ALU; en el código la lógica está distribuida entre `ObtenerValorOperando`, `LeerMemoria` y `EscribirMemoria`.

---

### 4.9 Visualización (shapes, rangos y convenciones en Excel)

**Elementos clave y convenciones:**

- Shapes nombrados: `C.P` (PC), `R.I` (IR), `RIM`, `EstadoALU`, `EstadoCache`, `EstadoDCache`, `OpCode`, `Operandos`, `Flags`.
- Rangos: `RANGO_MEMORIA_PRINCIPAL`, `RANGO_MEMORIA_VIRTUAL`, `RANGO_I_CACHE`, `RANGO_D_CACHE`, `RANGO_FETCH_BUFFER`, `RANGO_DECODE_BUFFER`, `RANGO_ALU_INPUT1`, `RANGO_ALU_INPUT2`, `RANGO_ALU_OUTPUT`.
- Colores constantes definidas en el módulo del usuario (`COLOR_ACTIVO`, `COLOR_CACHE_HIT`, `COLOR_REGISTRO_LECTURA`, etc.).
- La tabla pipeline (parte inferior de la hoja) muestra por fila de instrucción los estados F, D, EX, MEM, WB con colores.

**Uso:** las macros actualizan estos elementos para proporcionar una representación visual del estado del pipeline y memoria.

---

## 5. Flujo de datos y control (end-to-end)

1. Usuario carga ensamblador en Hoja1 (B3/B5) y presiona `CargarEnsamblador`.
2. `CargarEnsamblador` normaliza líneas, las copia a Hoja2 A3.., inicializa `memoriaStackGlobal`, limpia caches y llama `InicializarSistemaRegistros`.
3. Usuario puede ejecutar `AvanzarCiclo` repetidamente: cada llamada realiza Fetch→Decode→Execute→MemoryAccess→WriteBack con pausas para visualizar.
4. Alternativamente puede usar `SimularPipelineCPU` para ver tablas con múltiples instrucciones avanzando en paralelo (F/D/EX/MEM/WB) y ver cuándo aparecen `STALL`/`BUBBLE`.
5. Durante la ejecución, la ALU y las funciones de memoria actualizan `memoriaStackGlobal`, las celdas de caches y los registros a través de `LeerRegistro`/`EscribirRegistro`.

---

## 6. Parsing y representación de instrucciones (AT&T)

**Reglas implementadas en el código original:**

- Se usa `LimpiarInstruccion` y `NormalizarTexto` para normalizar espacios y eliminar comillas.
- `ParsearInstruccionDirecta` divide por el primer espacio para separado opcode y operandos.
- `ParsearOperando` clasifica operandos en `inmediato`, `registro`, `memoria`, o `etiqueta`.
- `NormalizarNombreRegistro` transforma `%eax`/`eax`/`ax` a `RAX`, procesa `R8`..`R15`.

---

## 7. Simulación del pipeline: algoritmo y reglas

**Estructura del bucle principal (tal como está en `SimularPipelineCPU`):**

- Inicializar arrays y conteos.
- `Do While` instrucciones pendientes o pipeline no vacío:

  - `ciclo = ciclo + 1`
  - Procesar WB: escribir WB en tabla, limpiar pipeline(5).
  - Procesar MEM: escribir MEM y mover pipeline(4)→pipeline(5).
  - Procesar EX: escribir EX y mover pipeline(3)→pipeline(4).
  - Procesar ID: detectar hazards comparando `regsFuente` con `RegistroDestino` de pipeline(3) y pipeline(4); si hazard → marcar STALL y BUBBLE; si no → mover pipeline(2)→pipeline(3).
  - Procesar IF: si no hay stall → introducir nueva instrucción y mover pipeline(1)→pipeline(2).
  - Pausa visual (`Application.Wait`) y `DoEvents`.

---

## 8. Manejo de hazards: RAW, load-use, forwarding y stalls

**RAW (Read After Write):**

- Detectado en ID comparando registros fuente con destinos en etapas posteriores.
- Si detectado, el simulador inserta `STALL` (visual) y evita `IF` ese ciclo.

**Load-use hazard:**

- Ocurre cuando una instrucción usa un registro que es destino de una load inmediatamente anterior.
- Con forwarding MEM→EX implementado, el load puede forwardear desde MEM a EX, pero aún así suele haber 1 ciclo de penalización si el load entrega el dato al final de MEM y la siguiente instrucción necesita el dato en EX.

**Forwarding (bypass):**

- En el primer módulo hay funciones visuales `CrearFlechaForwarding` para ilustrar forwarding.
- Para simularlo funcionalmente se debe implementar lógica que permita a instrucciones en ID inspeccionar resultados provisionales en pipeline(3) o pipeline(4) y, si disponible, usar ese valor en EX sin esperar a WB.

---

## 9. Ejemplos prácticos y tablas ciclo-a-ciclo

### 9.1 Ejemplo: `main`

**ASM (extracto):**

```
pushq %rbp
movq %rsp, %rbp
subq $48, %rsp
call __main
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

**Instrucciones relevantes para la operación `b=a+c`:**

- I1: `movl $9, -4(%rbp)` (store a)
- I2: `movl $11, -8(%rbp)` (store c)
- I3: `movl -4(%rbp), %edx` (load a→edx)
- I4: `movl -8(%rbp), %eax` (load c→eax)
- I5: `addl %edx, %eax` (eax = eax + edx)
- I6: `movl %eax, -12(%rbp)` (store b)

**Dependencias:** I5 depende de resultados de I3 e I4; I3 e I4 leen direcciones distintas (RBP-4 y RBP-8) por lo que no hay dependencia de memoria entre I1 e I2.

### 9.2 Tabla ciclo-a-ciclo (A) Sin forwarding — modelo conservador

| Ciclo | I1  | I2  | I3  | I4  | I5  | I6  |
| ----: | :-: | :-: | :-: | :-: | :-: | :-: |
|     1 | IF  |     |     |     |     |     |
|     2 | ID  | IF  |     |     |     |     |
|     3 | EX  | ID  | IF  |     |     |     |
|     4 | MEM | EX  | ID  | IF  |     |     |
|     5 | WB  | MEM | EX  | ID  | IF  |     |
|     6 |     | WB  | MEM | EX  | ID  | IF  |
|     7 |     |     | WB  | MEM | EX  | ID  |
|     8 |     |     |     | WB  | MEM | EX  |
|     9 |     |     |     |     | WB  | MEM |
|    10 |     |     |     |     |     | WB  |

**Interpretación:** la instrucción `addl` entra a EX en ciclo 7, cuando los loads han completado MEM/WB según el flujo; no se requiere stall adicional en esta tabla porque las cargas completan antes de que add llegue a EX en este horario. En un escenario más ajustado (si I4 se retrasara) podría necesitarse 1 burbuja.

### 9.3 Tabla ciclo-a-ciclo (B) Con forwarding MEM→EX y EX→EX (modelo optimizado)

Con forwarding, muchas dependencias por registros entre instrucciones consecutivas se resuelven sin insertar stalls.

| Ciclo | I1  | I2  | I3  | I4  | I5  | I6  |
| ----: | :-: | :-: | :-: | :-: | :-: | :-: |
|     1 | IF  |     |     |     |     |     |
|     2 | ID  | IF  |     |     |     |     |
|     3 | EX  | ID  | IF  |     |     |     |
|     4 | MEM | EX  | ID  | IF  |     |     |
|     5 | WB  | MEM | EX  | ID  | IF  |     |
|     6 |     | WB  | MEM | EX  | ID  | IF  |
|     7 |     |     | WB  | MEM | EX  | ID  |
|     8 |     |     |     | WB  | MEM | EX  |
|     9 |     |     |     |     | WB  | MEM |
|    10 |     |     |     |     |     | WB  |

En práctica la diferencia aparece cuando las cargas y el add están muy juntas (p.ej. si la carga está inmediatamente anterior y entrega el dato sólo al final de MEM). El forwarding puede eliminar un ciclo de stall.

### 9.4 Ejemplo: push/pop y acceso a stack (paso a paso)

ASM:

```
pushq %rax
popq %rbx
```

Paso a paso (conceptual):

1. `pushq %rax`: EX calcula nueva RSP = RSP - 8; MEM escribe `memoriaStackGlobal("MEM_<RSP>") = valor(%rax)`.
2. `popq %rbx`: MEM lee `memoriaStackGlobal("MEM_<RSP>")` y EX/ WB escribe en `%rbx`; EX actualiza RSP = RSP + 8.

Visualmente `EstadoDCache` y la tabla de memoria muestran la entrada `Addr:...` y el valor.

---

## 10. Anexo: resumen de funciones VBA

(Se listan las funciones tal como aparecen en los módulos aportados por el usuario.)

- `Sub CrearDiagramaPipeline()` – crea diagrama con shapes.

- `Sub CrearLeyendaEtapa(ws,x,y,etapa,nombre,color,desc)` – crea leyenda.

- `Sub CrearInstruccion(ws,x,y,inst,desc,hazard)` – dibuja instrucción.

- `Sub CrearPipelineCompleto(ws,y,numInst,hazard)` – dibuja pipeline por instrucción.

- `Sub CrearAlertaHazard(ws,x,y,texto)` – dibuja cuadro alerta hazard.

- `Sub CrearFlechaForwarding(ws,x1,y1,x2,y2)` – crea conector visual de forwarding.

- `Sub LimpiarHoja(ws)` – borra shapes y limpia celdas.

- `Type InstruccionPipeline` – estructura para pipeline (en segundo archivo del usuario).

- `Sub SimularPipelineCPU(rangoInstrucciones As Range, rangoPipeline As Range)` – simula pipeline en modo tabla.

- `Function HayInstruccionesEnPipeline(pipeline() As InstruccionPipeline) As Boolean` – chequea pipeline no vacío.

- `Sub ExtraerRegistros(instruccion As String, ByRef regDestino As String, ByRef regsFuente As String)` – parser simple para registros.

- `Option Explicit` (en módulo 3 original) – se recomienda mantener en todos.

- `Type InstruccionASM` – estructura para instrucción parseada (módulo 3).

- `Sub InicializarSistemaRegistros()` – detecta registros y renderiza tabla en Excel.

- `Function LimpiarInstruccion(instruccion As String) As String` – limpia espacios.

- `Function ExtraerRegistrosDeInstruccion(instruccion As String) As Collection` – extrae tokens `%reg`.

- `Function NormalizarNombreRegistro(regRaw As String) As String` – normaliza nombres de registro.

- `Sub RenderizarRegistrosEnExcel()` – pinta registros en hoja (problema Cells vs Range detectado).

- `Function LeerRegistro(nombreReg As String) As Long` – devuelve valor (crea si no existe).

- `Sub EscribirRegistro(nombreReg As String, valor As Long)` – actualiza valor y hoja.

- `Sub ResaltarRegistro(nombreReg As String, colorFondo As Long)` – resalta celda del registro.

- `Sub ParsearOperando(operando As String, ByRef tipo As String, ByRef valor As Variant)` – clasifica operandos.

- `Function ObtenerValorOperando(tipo As String, valor As Variant) As Long` – obtiene valor numérico de operando.

- `Function LeerMemoria(expresion As String) As Long` – lee memoria desde memoriaStackGlobal.

- `Sub EscribirMemoria(expresion As String, valor As Long)` – escribe memoria.

- `Function SimularLecturaMemoria(expresion As String) As Long` – func. auxiliar para datos.

- `Sub ParsearInstruccion(instruccion As String, ByRef resultado As InstruccionASM)` – parsea instrucción.

- `Sub EjecutarEnALU(Operacion As String)` – ejecuta instrucción en ALU (usa ParsearInstruccionDirecta).

- `Sub ParsearInstruccionDirecta(...)` – parseo directo y salida de operandos.

- `Sub WriteBack()` – escribe Z1/Z2 a registro y limpia buffers.

- `Sub CargarEnsamblador()` – carga código desde Hoja1 y prepara memoria/regs.

- `Sub AvanzarCiclo()` – secuencia Fetch→Decode→Execute→MemoryAccess→WriteBack.

- `Sub Fetch()`, `Sub Decode()`, `Sub Execute()`, `Sub MemoryAccess()` – etapas.

- `Sub EjecutarMOVSS`, `Sub EjecutarMOV`, `Sub EjecutarPUSH`, `Sub EjecutarPOP`, `Sub EjecutarSUBQ`, `Sub EjecutarComparacion` – manejadores específicos.

- `Sub CargarEnCache`, `Sub CargarEnCacheAcumulativo`, `Function BuscarEnCache` – manejo básico de caches.

- `Sub ResaltarTemporal(rango As Range, colorRGB As Long, segundos As Double)` – resalta rango temporalmente.

- `Sub LimpiarMemoria(memoria As Range, Optional colorEntrada As Long = -1)` – limpia bloques de memoria visual.

- `Sub Swap(origen As Range, destino As Range, celdaCompleta As Range)` – mueve datos entre ranges.

- `Sub CompactarMemoria(rango As Range)` – compacta memoria visual.

- `Sub MostrarMemoriaFormatted()` – muestra memoria stack ordenada.

- `Sub TestRegistrosInfinitos()`, `Sub ResetearSimulador()`, `Sub ConfigurarStackBase(valorBase As Long)` — utilidades.
