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
    matriz.add(8, 0, 1); // Algo falla, este se imprime después del 7 y 5
    matriz.add(10, 4, 0);
    matriz.add(3, 2, 0);
    matriz.add(7, 0, 3);
    matriz.add(9, 4, 3);
    matriz.add(6, 1, 4);
    matriz.add(4, 3, 2);
    matriz.add(2, 3, 4);
    matriz.add(1, 1, 1);
    matriz.add(11, 2, 3); // Debería fallar
    matriz.add(7, 3, 0);
    matriz.add(12, -1, 2); // Debería fallar
    matriz.add(0, 2, 2); // Debería fallar

    matriz.printStoredValues();

    return 0;
}

bool App::iniciarMatriz() {
    matriz = SparseMatrix();
    return true;
}