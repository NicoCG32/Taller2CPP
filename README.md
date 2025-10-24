# Taller 2 - Estructuras de Datos

Asignatura: Estructura de Datos – 2° Semestre 2025

Profesor: Bastián Ruiz

Ayudante: Sebastián Pleticosic

Alumno: Pablo Guzmán Vargas – Paralelo C2

## Descripción del proyecto

Implementación, desde cero, de una matriz poco poblada (sparse) utilizando listas enlazadas con nodos centinela por filas y columnas. El sistema incluye un modo manual para operar con dos matrices (Principal y Second) y un modo de pruebas para generar matrices y medir el desempeño de las operaciones principales.

Operaciones destacadas (clase `SparseMatrix`):
- `add(valor, x, y)`: inserta/actualiza un valor en (x, y).
- `get(x, y)`: obtiene el valor en (x, y) o 0 si no existe.
- `remove(x, y)`: elimina el nodo si existe.
- `density()`: calcula la densidad de la matriz.
- `printStoredValues()` y `printMatrix()`: visualización.
- `multiply(B)`: multiplicación de matrices con expansión artificial cuando las dimensiones son incompatibles.
- Utilidades: `countNonZero()`, `compact()`, `getWidth()`, `getHeight()`. Estas utilidades se implementaron únicamente para facilitar el estudio de la matriz (visualización, medición y depuración) y no forman parte del mínimo indispensable de la estructura.

Modo PRUEBAS (benchmark):
- add: cada repetición usa una matriz vacía y el mismo conjunto fijo de m coordenadas; se acumula tiempo hasta ≥ 10 ms (con 2 warmups).
- get: usa siempre la misma matriz base y el mismo set fijo de consultas; se acumula hasta ≥ 10 ms (con 2 warmups).
- multiply: misma A y B fijas, con 2 warmups; se ejecuta exactamente 10 repeticiones y se reporta el promedio.

## Estructura de carpetas

```
Taller2CPP/
├─ README.md
├─ build/
├─ include/
│  ├─ App.h
│  ├─ Node.h
│  └─ SparseMatrix.h
├─ src/
│  ├─ App.cpp
│  ├─ Node.cpp
│  └─ SparseMatrix.cpp
└─ run.bat

```
## Requisitos

- Windows con g++ en el PATH (MinGW-w64 o MSYS2).  
	Si `g++` no es reconocido, instala MSYS2/MinGW y agrega `mingw64\bin` al PATH.
- Terminal PowerShell o CMD.

## Compilar y ejecutar (Terminal)

Desde la carpeta raíz del proyecto:

Compilar (genera `build/taller.exe`):
```powershell
g++ -std=gnu++17 -O2 -Wall -Wextra -Iinclude -o build/taller.exe src/App.cpp src/SparseMatrix.cpp src/Node.cpp
```
Ejecutar:
```powershell
./build/taller.exe
```
En CMD, puedes usar `build\taller.exe`.

## Compilar y ejecutar con script

Opción Batch (CMD o doble clic):

```cmd
run.bat
```

## Documentación (Doxygen)

El proyecto incluye documentación generada con Doxygen. Para generarla:

1. Asegúrate de tener Doxygen instalado: https://www.doxygen.nl/download.html
2. Desde la carpeta `docs/` ejecuta:
   ```powershell
   cd docs
   doxygen Doxyfile
   ```
3. Abre `docs/html/index.html` en tu navegador para ver la documentación.

Nota:
- Los diagramas están desactivados por defecto. Si tienes Graphviz instalado y quieres habilitar diagramas de clases y call graphs, edita `docs/Doxyfile` y cambia `HAVE_DOT = NO` a `HAVE_DOT = YES`.
- La salida HTML queda en `docs/html/`.

## Uso rápido

1) Al ejecutar, verás el estado de las matrices y un menú principal.
- Modo MANUAL: agregar/obtener/eliminar, imprimir, densidad, multiplicar entre Principal y Second.
- Modo PRUEBAS: generar matrices con distintos tamaños/densidades y medir add/get/multiply con metodología establecida.

2) En PRUEBAS:
- add: ingresa m (inserciones por repetición). El benchmark usa siempre las mismas m coordenadas sobre una matriz vacía por repetición. Se acumula hasta 10 ms y se reporta el promedio por operación (ms, ns, ps).
- get: ingresa n (consultas por repetición). Usa siempre la misma matriz base y el mismo set de consultas. Se acumula hasta 10 ms y se reporta el promedio.
- multiply: se fija A y se genera B una vez; tras 2 warmups se ejecuta 10 veces y se reporta promedio.

## Mediciones: funcionamiento y consideraciones

- Reloj y formato: se usa `std::chrono::steady_clock` para evitar saltos del reloj del sistema. Se reportan tiempos en ms, ns y ps. Los promedios se calculan con `double` para evitar truncamientos (p. ej., 0 ns).
- Ruido y warmup: no hay impresiones dentro de los bucles medidos. Se realizan 2 iteraciones de calentamiento fuera del cronómetro para estabilizar cachés y branch predictors.
- add: solicita m y genera una sola vez un conjunto fijo de m coordenadas únicas y valores. Cada repetición se hace sobre una matriz vacía nueva. Se repiten bloques hasta acumular ≥ 10 ms; se informa el total y el promedio por operación.
- get: genera una sola vez un set fijo de n consultas sobre la misma matriz base. Se repiten bloques hasta acumular ≥ 10 ms; se informa el total y el promedio por operación.
- multiply: fija A (base) y crea B una sola vez fuera del cronómetro; tras 2 warmups, ejecuta exactamente 10 multiplicaciones. Se mide solo la llamada a `multiply` y la destrucción del resultado ocurre fuera de la medición.
- Consideraciones: se evita medir constructores/destructores dentro del intervalo; los datos de entrada (coordenadas o matrices) se fijan para garantizar repetibilidad; no se realiza I/O durante la medición.

## Notas

- Los tiempos se reportan en milisegundos, nanosegundos y picosegundos.  
- Para resultados estables, se evita imprimir dentro de los bucles medidos y se separan warmups de mediciones.
- La implementación de los métodos originales/núcleo de `SparseMatrix` (estructura, `add`, `get`, `remove`, `multiply`, y lógica de listas) fue realizada de forma autónoma por el estudiante. La implementación de los menús (especialmente el modo PRUEBAS) y de utilidades/funciones secundarias se realizó con apoyo de IA para agilizar el flujo de pruebas y la instrumentación.

