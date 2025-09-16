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

    matriz.printStoredValues();
    cout << "Valor en (2,3): " << matriz.get(2, 3) << endl;
    cout << "Valor en (0,1): " << matriz.get(0, 1) << endl;
    cout << "Densidad: " << matriz.density() << "%" << endl;

    cout << endl;
    
    matriz.remove(2, 3);
    matriz.printStoredValues();
    cout << "Valor en (2,3): " << matriz.get(2, 3) << endl;
    cout << "Valor en (0,1): " << matriz.get(0, 1) << endl;
    cout << "Densidad: " << matriz.density() << "%" << endl;

    return 0;
}

bool App::iniciarMatriz() {
    matriz = SparseMatrix();
    return true;
}