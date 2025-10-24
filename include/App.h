#pragma once

#include "SparseMatrix.h"

class App {

private:
    SparseMatrix* principal;
    SparseMatrix* second;
    
    /**
     * Inicia las matrices dispersas utilizadas en la aplicación.
     * 
     * Esta función crea e inicializa las matrices dispersas "principal"
     * y "second" que serán utilizadas en la aplicación. Si las matrices
     * ya existen, se eliminan antes de crear nuevas instancias.
     * 
     * PRECONDICIONES:
     * - Ninguna.
     * 
     * POSTCONDICIONES:
     * - Las matrices "principal" y "second" están inicializadas y listas
     *   para su uso.
     * - Si ocurre un error durante la inicialización, las matrices
     *   permanecen nulas.
     * 
     * @return bool true si las matrices se iniciaron correctamente,
     *              false en caso de error.
     */
    bool iniciarMatriz();

    /**
     * Limpia la pantalla de la consola.
     * 
     * Esta función utiliza comandos del sistema para limpiar la pantalla,
     * dependiendo del sistema operativo en uso (Windows o Unix).
     * 
     * Se recomienda utilizar esta función antes de mostrar cualquier
     * menú o estado de las matrices para mejorar la legibilidad.
     */
    void limpiarPantalla();

    /**
     * Muestra el estado actual de ambas matrices en la consola.
     * 
     * Esta función imprime las matrices "principal" y "second" en su
     * estado actual, mostrando sus contenidos en formato legible.
     * Si alguna de las matrices no ha sido inicializada, se indica
     * que no está disponible.
     */
    void mostrarEstadoMatrices();

    /**
     * Muestra el menú principal de la aplicación.
     * 
     * Esta función imprime en la consola las opciones disponibles en el
     * menú principal, permitiendo al usuario seleccionar la acción a
     * realizar.
     */
    void mostrarMenuPrincipal();

    /**
     * Muestra el menú del modo manual.
     * 
     * Esta función imprime en la consola las opciones disponibles en el
     * menú del modo manual, permitiendo al usuario seleccionar la acción a
     * realizar.
     */
    void mostrarMenuManual();

    /**
     * Muestra el menú del modo pruebas.
     * 
     * Esta función imprime en la consola las opciones disponibles en el
     * menú del modo pruebas, permitiendo al usuario seleccionar la acción a
     * realizar.
     */
    void mostrarMenuPruebas();

    /**
     * Muestra el menú para una matriz específica.
     * 
     * Esta función imprime en la consola las opciones disponibles en el
     * menú para la matriz especificada, permitiendo al usuario seleccionar
     * la acción a realizar.
     */
    void mostrarMenuMatriz(int numeroMatriz);

    /**
     * Procesa la opción seleccionada en el menú de una matriz.
     * 
     * PRECONDICIONES:
     * - opcion debe ser una opción válida del menú de la matriz.
     * - numeroMatriz debe ser 1 o 2.
     * 
     * POSTCONDICIONES:
     * - Se ejecuta la acción correspondiente a la opción seleccionada.
     * - Se muestran mensajes de confirmación o error según corresponda.
     * - No se modifica el estado de las matrices a menos que la opción
     *  lo requiera explícitamente.
     * 
     * Esta función se encarga de ejecutar la acción correspondiente a la
     * opción seleccionada en el menú de la matriz especificada.
     * 
     * @param opcion Opción seleccionada por el usuario.
     * @param numeroMatriz Número de la matriz (1 o 2) sobre la cual se
     *                     realizará la acción.
     */
    void procesarOpcionMatriz(int opcion, int numeroMatriz);

    /**
     * Guarda el resultado de una operación en una de las matrices.
     * 
     * PRECONDICIONES:
     * - resultado debe ser un puntero válido a una matriz dispersa.
     * 
     * POSTCONDICIONES:
     * - Si el usuario elige guardar el resultado, la matriz
     * correspondiente se actualiza con el nuevo valor.
     * - Si el usuario decide no guardar el resultado, la matriz
     * resultante se elimina para evitar fugas de memoria.
     * - Se muestran mensajes de confirmación o error según corresponda.
     * 
     * Esta función toma un puntero a una matriz dispersa como resultado
     * de una operación y lo guarda en la matriz correspondiente (principal
     * o secundaria) según el estado actual de la aplicación.
     * 
     * @param resultado Puntero a la matriz dispersa que contiene el resultado
     *                  de la operación.
     */
    void guardarResultado(SparseMatrix* resultado);

    /**
     * Genera una matriz dispersa aleatoria.
     * 
     * Esta función crea una matriz dispersa con un número específico de
     * elementos no nulos, distribuidos aleatoriamente en la matriz.
     * 
     * PRECONDICIONES:
     * - matriz debe ser un puntero válido a una matriz dispersa.
     * - cantidadDatos debe ser un entero positivo.
     * - densidadObjetivo debe estar en el rango [0, 100].
     * 
     * POSTCONDICIONES:
     * - La matriz apuntada por 'matriz' contiene 'cantidadDatos' elementos
     *  no nulos distribuidos aleatoriamente.
     * - La densidad de la matriz se aproxima a 'densidadObjetivo'.
     * - No se producen fugas de memoria.
     * 
     * @param matriz Puntero a la matriz dispersa a inicializar.
     * @param cantidadDatos Cantidad de elementos no nulos a generar.
     * @param densidadObjetivo Densidad objetivo de la matriz (0 a 100).
     */
    void generarMatrizAleatoria(SparseMatrix* matriz, int cantidadDatos, int densidadObjetivo);

public:
    App();
    ~App();
    int main();
};