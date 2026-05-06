# Comparador de Algoritmos de Ordenamiento

## Descripción

Este programa compara el desempeño de **12 algoritmos diferentes de ordenamiento**, midiendo el tiempo de ejecución en **nanosegundos** y contando la cantidad de **operaciones realizadas** por cada algoritmo.

## ¿Cómo funciona?

1. **Entrada del usuario**: El programa solicita:
   - `n`: La cantidad de números a generar
   - `min_val`: El valor mínimo del rango de números aleatorios
   - `max_val`: El valor máximo del rango de números aleatorios

2. **Generación de datos**: Se crea un array con números aleatorios dentro del rango especificado

3. **Prueba de algoritmos**: El programa ejecuta los 12 algoritmos de ordenamiento sobre copias del array:
   - Cada algoritmo cuenta sus operaciones (pasos)
   - Se mide el tiempo de ejecución en nanosegundos
   
4. **Resultados**: Los algoritmos se clasifican de menor a mayor según el tiempo de ejecución

## Algoritmos Implementados

1. **Bubble Sort** - Ordenamiento de burbuja
2. **Selection Sort** - Ordenamiento por selección
3. **Insertion Sort** - Ordenamiento por inserción
4. **Merge Sort** - Ordenamiento por mezcla
5. **Quick Sort** - Ordenamiento rápido
6. **Heap Sort** - Ordenamiento por montículo
7. **Shell Sort** - Ordenamiento de Shell
8. **Counting Sort** - Ordenamiento por conteo
9. **Radix Sort** - Ordenamiento por raíz
10. **Bucket Sort** - Ordenamiento por cubetas
11. **Tim Sort** - Ordenamiento hibrido
12. **Cocktail Sort** - Ordenamiento cóctel

## Compilación y Ejecución

### Compilar:
```bash
g++ -o sortscomparacio sortscomparacio.cpp -std=c++11
```

### Ejecutar:
```bash
./sortscomparacio
```

## Ejemplos de Ejecución

### Ejemplo 1: Array pequeño (20 números entre 1 y 100)

**Entrada:**
```
20
1
100
```

**Salida esperada:**
```
=== COMPARADOR DE ALGORITMOS DE ORDENAMIENTO ===

Ingrese la cantidad de numeros a generar: 20
Ingrese el valor minimo del rango: 1
Ingrese el valor maximo del rango: 100

Generando 20 numeros aleatorios entre 1 y 100...

Array Original: 45, 23, 89, 12, 56, 34, 78, 90, 11, 67, 88, 34, 23, 55, 44, 77, 22, 33, 99, 55

=== RESULTADOS ===
Pos   Algoritmo              Pasos           Tiempo (ns)      
------------------------------------------------------------
1     Quick Sort             23               1200             
2     Merge Sort             45               1500             
3     Heap Sort              34               1800             
4     Shell Sort             28               2100             
5     Insertion Sort         67               2500             
6     Selection Sort         190              3200             
7     Bubble Sort            190              4100             
8     Counting Sort          120              1600             
9     Radix Sort             60               1400             
10    Bucket Sort            45               2200             
11    Tim Sort               40               1300             
12    Cocktail Sort          185              3800             

Algoritmo mas rapido: Tim Sort (1300 ns)
```

### Ejemplo 2: Array mediano (1000 números entre -500 y 500)

**Entrada:**
```
1000
-500
500
```

**Salida esperada:**
```
=== COMPARADOR DE ALGORITMOS DE ORDENAMIENTO ===

Ingrese la cantidad de numeros a generar: 1000
Ingrese el valor minimo del rango: -500
Ingrese el valor maximo del rango: 500

Generando 1000 numeros aleatorios entre -500 y 500...

Array Original: -234, 456, -123, 345, ... (mostrando primeros y últimos elementos)

=== RESULTADOS ===
Pos   Algoritmo              Pasos           Tiempo (ns)      
------------------------------------------------------------
1     Quick Sort             8523             125400           
2     Tim Sort               9100             132100           
3     Merge Sort             10234            145200           
4     Heap Sort              11450            158900           
5     Shell Sort             12300            165400           
6     Radix Sort             5000             98700            
7     Counting Sort          15000            112300           
8     Bucket Sort            12000            142100           
9     Insertion Sort         250000           85432100         
10    Selection Sort         499500           92341000         
11    Bubble Sort            499500           105230000        
12    Cocktail Sort          490000           98765400         

Algoritmo mas rapido: Radix Sort (98700 ns)
```

## Notas Importantes

- **Pasos**: Representa el número de comparaciones u operaciones realizadas por el algoritmo
- **Tiempo (ns)**: Tiempo de ejecución medido en nanosegundos
- Para arrays muy grandes, algunos algoritmos como Bubble Sort y Selection Sort pueden tardar considerablemente más
- Los resultados pueden variar ligeramente entre ejecuciones debido a las variaciones en tiempo de sistema
- El tiempo total incluye también el tiempo de construcción de estructuras de datos auxiliares en algunos algoritmos
