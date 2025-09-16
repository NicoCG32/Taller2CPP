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

    cout << "Proyecto Matrices Poco Pobladas!" << endl;

    matriz.add(5, 2, 3);
    matriz.add(8, 0, 1); 
    matriz.add(10, 4, 0);
    matriz.add(3, 2, 0);
    matriz.add(7, 0, 3);

    cout << "Valor en (2,3): " << matriz.get(2, 3) << endl;
    cout << "Valor en (0,1): " << matriz.get(0, 1) << endl;
    cout << "Valor en (4,0): " << matriz.get(4, 0) << endl;
    cout << "Valor en (2,0): " << matriz.get(2, 0) << endl;
    cout << "Valor en (0,3): " << matriz.get(0, 3) << endl;
    cout << "Valor en (1,1): " << matriz.get(1, 1) << endl; // No existe
    cout << "Valor en (-1,2): " << matriz.get(-1, 2) << endl; // Posición inválida

    return 0;
}

bool App::iniciarMatriz() {
    matriz = SparseMatrix();
    return true;
}