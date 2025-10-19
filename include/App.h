#pragma once

#include "SparseMatrix.h"

class App {

private:
    SparseMatrix* principal;
    SparseMatrix* second;
    
    void mostrarMenuPrincipal();
    void mostrarMenuMatriz(int numeroMatriz);
    void procesarOpcionMatriz(int opcion, int numeroMatriz);
    void guardarResultadoMultiplicacion(SparseMatrix* resultado);

public:
    App();
    ~App();
    int main();
    bool iniciarMatriz();
};