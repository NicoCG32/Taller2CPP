#include "SparseMatrix.h"

#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix() {
    cout << "Matriz creada con éxito." << endl;
}

SparseMatrix::~SparseMatrix() {}

void SparseMatrix::add(int value, int xPos, int yPos) {}

int SparseMatrix::get(int xPos, int yPos) {
    return 0;
}

void SparseMatrix::remove(int xPos, int yPos) {}

void SparseMatrix::printStoredValues() {}

int SparseMatrix::density() {
    return 0;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    return nullptr;
}