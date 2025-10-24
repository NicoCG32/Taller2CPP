#pragma once

#include "Node.h"

/**
 * Esta clase define una matriz dispersa basada en listas ligadas con nodos centinela.
 * Administra inserciones, consultas, eliminaciones, recorrido e impresión de valores no-cero,
 * además de calcular la densidad y realizar la multiplicación entre matrices dispersas,
 * expandiendo artificialmente dimensiones cuando es necesario para compatibilizar.
 *
 * @author Pablo Guzmán
 */
class SparseMatrix {

private:
    Node* start;
    
public:
     /**
     * Constructor por defecto de la matriz dispersa.
     *
     * PRECONDICIONES:
     * Ninguna.
     *
     * POSCONDICIONES:
     * La matriz queda vacía, lista para operar.
     */
    SparseMatrix();

    /**
     * Destructor de la matriz dispersa.
     *
     * PRECONDICIONES:
     * Ninguna.
     *
     * POSCONDICIONES:
     * No quedan fugas de memoria asociadas a la matriz.
     */
    ~SparseMatrix();

    /**
     * Inserta un valor no-cero en la posición indicada.
     *
     * PRECONDICIONES:
     * - value != 0.
     * - xPos >= 0 y yPos >= 0.
     * - No debe existir ya un valor en (xPos, yPos).
     *
     * POSCONDICIONES:
     * - Si es válido, el valor queda almacenado en (xPos, yPos).
     * - Si no es válido, no se realizan cambios.
     *
     * @param value Valor entero a insertar (no se almacenan ceros).
     * @param xPos  Coordenada de columna (x) donde insertar (>= 0).
     * @param yPos  Coordenada de fila (y) donde insertar (>= 0).
     */
    void add(int value, int xPos, int yPos);

    /**
     * Obtiene el valor almacenado en una posición.
     *
     * PRECONDICIONES:
     * - xPos >= 0 y yPos >= 0.
     *
     * POSCONDICIONES:
     * - No modifica la matriz.
     *
     * @param xPos Coordenada de columna (x) a consultar (>= 0).
     * @param yPos Coordenada de fila (y) a consultar (>= 0).
     * @return int Valor almacenado en (xPos, yPos) o 0 si no existe.
     */
    int get(int xPos, int yPos);

    /**
     * Elimina el valor almacenado en una posición y compacta la estructura.
     *
     * PRECONDICIONES:
     * - xPos >= 0 y yPos >= 0.
     * - Debe existir un valor en (xPos, yPos) para que haya efecto.
     *
     * POSCONDICIONES:
     * - El valor en (xPos, yPos) es removido si existía.
     * - Las filas/columnas vacías se eliminan (la matriz puede reducir
     *   su tamaño lógico al remover centinelas de borde vacíos).
     *
     * @param xPos Coordenada de columna (x) a eliminar (>= 0).
     * @param yPos Coordenada de fila (y) a eliminar (>= 0).
     */
    void remove(int xPos, int yPos);

    /**
     * Imprime por consola todos los valores almacenados (no-cero).
     *
     * PRECONDICIONES:
     * Ninguna.
     *
     * POSCONDICIONES:
     * No modifica la matriz.
     */
    void printStoredValues();

    /**
     * Calcula la densidad de la matriz en porcentaje de celdas no-cero.
     *
     * PRECONDICIONES:
     * Ninguna.
     *
     * POSCONDICIONES:
     * No modifica la matriz.
     *
     * @return int Porcentaje (entero) de densidad en el rango [0, 100].
     */
    int density();

    /**
     * Multiplica la matriz actual por otra matriz dispersa con expansión opcional.
     *
     * PRECONDICIONES:
     * - El puntero 'second' debe ser válido (no nulo).
     *
     * POSCONDICIONES:
     * - Devuelve una nueva matriz con el resultado de la multiplicación.
     * - Las matrices de entrada pueden haber agregado centinelas de borde
     *   para compatibilizar dimensiones (expansión lógica sin agregar valores).
     * - No se insertan valores no-cero nuevos en las matrices de entrada.
     *
     * @param second Puntero a la segunda matriz (multiplicando derecho).
     * @return SparseMatrix* Nueva matriz con el resultado de la multiplicación.
     */
    SparseMatrix* multiply(SparseMatrix* second);

    /* Métodos auxiliares SÓLO para el ESTUDIO de SparseMatrix */
    
    /**
     * Obtiene el valor almacenado sin imprimir mensajes.
     * Método interno para uso de printMatrix y otras operaciones silenciosas.
     *
     * @param xPos Coordenada de columna (x) a consultar (>= 0).
     * @param yPos Coordenada de fila (y) a consultar (>= 0).
     * @return int Valor almacenado en (xPos, yPos) o 0 si no existe.
     */
    int getValueSilent(int xPos, int yPos);

    /**
     * Imprime la matriz completa, incluyendo ceros, en formato de lista 2D.
     *
     * PRECONDICIONES:
     * Ninguna.
     *
     * POSCONDICIONES:
     * No modifica la matriz.
     */
    void printMatrix();

    /**
     * Cuenta la cantidad de valores no-cero almacenados en la matriz.
     * No imprime mensajes.
     * @return int Cantidad de nodos con valor distinto de 0.
     */
    int countNonZero();

    /**
     * Compacta la matriz eliminando centinelas de borde vacíos.
     * 
     * PRECONDICIONES:
     * Ninguna.
     * 
     * POSCONDICIONES:
     * La matriz queda compactada sin centinelas de borde vacíos.
     */
    void compact();

    /**
     * Obtiene la altura de la matriz.
     *
     * @return int Altura de la matriz (número de filas).
     */
    int getHeight();

    /**
     * Obtiene la anchura de la matriz.
     *
     * @return int Anchura de la matriz (número de columnas).
     */
    int getWidth();
};