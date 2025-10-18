#include "App.h"
#include <iostream>
using namespace std;

// Función MAIN
int main() {
    App app;
    return app.main();
}

int App::main() {
    if (!iniciarMatriz()) {
        cout << "Error al iniciar la matriz." << endl;
        return -1;
    }
    SparseMatrix* resultado = nullptr;
    cout << "Proyecto Matrices Poco Pobladas!" << endl;

    // Prueba de multiplicación
    
    matriz.add(5, 1, 0);
    matriz.add(8, 0, 1); 
    
    cout << "Matriz N°1:" << endl;
    matriz.printStoredValues();
    
    SparseMatrix segundaMatriz;
    segundaMatriz.add(2, 0, 0);
    segundaMatriz.add(3, 1, 0);
    segundaMatriz.add(4, 0, 1);

    cout << "Matriz N°2:" << endl;
    segundaMatriz.printStoredValues();

    resultado = matriz.multiply(&segundaMatriz);
    cout << "Matriz Resultante de la Multiplicación:" << endl;
    resultado->printStoredValues();

    // Más pruebas

    matriz.add(10, 2, 2);
    segundaMatriz.add(5, 2, 0);
    segundaMatriz.add(7, 1, 2);
    
    cout << "Matriz N°1 Actualizada:" << endl;
    matriz.printStoredValues();
    cout << "Matriz N°2 Actualizada:" << endl;
    segundaMatriz.printStoredValues();

    resultado = matriz.multiply(&segundaMatriz);
    cout << "Matriz Resultante de la Multiplicación Actualizada:" << endl;
    resultado->printStoredValues();

    delete resultado;

    // Pruebas con matrices no cuadradas

    SparseMatrix terceraMatriz;
    terceraMatriz.add(1, 0, 0);
    terceraMatriz.add(2, 0, 2);
    terceraMatriz.add(3, 0, 1);

    cout << "Matriz N°1 No Cuadrada:" << endl;
    terceraMatriz.printStoredValues();

    SparseMatrix cuartaMatriz;
    cuartaMatriz.add(4, 0, 0);
    cuartaMatriz.add(5, 1, 0);
    cuartaMatriz.add(6, 2, 0);

    cout << "Matriz N°2 No Cuadrada:" << endl;
    cuartaMatriz.printStoredValues();

    resultado = terceraMatriz.multiply(&cuartaMatriz);  // 3x1 * 1x3 = 3x3
    cout << "Matriz Resultante de la Multiplicación No Cuadrada:" << endl;
    resultado->printStoredValues();
    delete resultado;


    resultado = cuartaMatriz.multiply(&terceraMatriz);  // 1x3 * 3x1 = 1x1
    cout << "Matriz Resultante de la Multiplicación No Cuadrada Inversa:" << endl;
    resultado->printStoredValues(); 
    delete resultado;

    return 0;
}

bool App::iniciarMatriz() {
    matriz = SparseMatrix();
    return true;
}