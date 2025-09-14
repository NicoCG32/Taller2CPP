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

    return 0;
}

bool App::iniciarMatriz() {
    matriz = SparseMatrix();
    return true;
}