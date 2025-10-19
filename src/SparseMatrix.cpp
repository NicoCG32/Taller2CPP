#include "SparseMatrix.h"

#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix() {
    start = new Node(0, -1, -1);
    start->setRight(start);
    start->setDown(start);
    start->setLeft(start);
    start->setUp(start);
}

SparseMatrix::~SparseMatrix() {
    
    Node* cursor = start->getDown();
    while (cursor != start) {
        Node* limite = cursor;
        cursor = cursor->getRight();

        while (cursor != limite) {
            Node* temp = cursor;
            cursor = cursor->getRight();
            delete temp;
        }
        Node* temp = limite;
        limite = limite->getDown();
        delete temp;
        cursor = limite;
    }
    delete start;
}

void SparseMatrix::add(int value, int xPos, int yPos) {

    // Verificación: valor cero no es válido (no tiene sentido almacenar ceros)
    if (value == 0) {
    cout << "No se pueden agregar valores cero.\n";
        return;
    }

    // Verificación: posiciones negativas no son válidas
    if (xPos < 0 || yPos < 0) {
    cout << "Posiciones inválidas: (" << xPos << "," << yPos << ")\n";
        return;
    }

    int x = -1;
    int y = -1;

    // Verificación: no existe ya un valor en la posición
    Node* tempX = start;
    Node* centinelaX;
    while (x < xPos) {
        if (tempX->getRight() == start) {
            centinelaX = new Node(0, x + 1, -1);

            tempX->setRight(centinelaX);
            centinelaX->setLeft(tempX);

            centinelaX->setRight(start);
            start->setLeft(centinelaX);

            centinelaX->setUp(centinelaX);
            centinelaX->setDown(centinelaX);

            tempX = centinelaX;
        } else {
            tempX = tempX->getRight();
        }
        x++;
    }
    centinelaX = tempX;

    Node* tempY = start;
    Node* centinelaY;
    while (y < yPos) {
        if (tempY->getDown() == start) {
            centinelaY = new Node(0, -1, y + 1);

            tempY->setDown(centinelaY);
            centinelaY->setUp(tempY);

            centinelaY->setDown(start);
            start->setUp(centinelaY);

            centinelaY->setRight(centinelaY);
            centinelaY->setLeft(centinelaY);

            tempY = centinelaY;
        } else {
            tempY = tempY->getDown();
        }
        y++;
    }
    centinelaY = tempY;

    tempX = centinelaX->getDown();
    while (tempX->getY() != -1 && tempX->getY() < yPos) {
        tempX = tempX->getDown();
    }
    tempY = centinelaY->getRight();
    while (tempY->getX() != -1 && tempY->getX() < xPos) {
        tempY = tempY->getRight();
    }
    
    if (tempY->getX() == xPos || tempX->getY() == yPos) {
        cout << "Ya hay un valor en la posicion: (" << xPos << "," << yPos << ")" << endl;
        return;
    }

    // Inserción
    Node* newNode = new Node(value, xPos, yPos);
    Node* temp;

    if (centinelaX->getDown() == centinelaX) {
        centinelaX->setDown(newNode);
        newNode->setUp(centinelaX);
        centinelaX->setUp(newNode);
        newNode->setDown(centinelaX);

    } else {
        tempX = centinelaX->getDown();
        y = tempX->getY();

        while (y != -1 && y < yPos) {
            tempX = tempX->getDown();
            y = tempX->getY();
        }
        
        temp = tempX->getUp();
        temp->setDown(newNode);
        newNode->setUp(temp);
        tempX->setUp(newNode);
        newNode->setDown(tempX);
    }

    if (centinelaY->getRight() == centinelaY) {
        centinelaY->setRight(newNode);
        newNode->setLeft(centinelaY);
        centinelaY->setLeft(newNode);
        newNode->setRight(centinelaY);

    } else {
        tempY = centinelaY->getRight();
        x = tempY->getX();

        while (x != -1 && x < xPos) {
            tempY = tempY->getRight();
            x = tempY->getX();
        }
        
        temp = tempY->getLeft();
        temp->setRight(newNode);
        newNode->setLeft(temp);
        tempY->setLeft(newNode);
        newNode->setRight(tempY);
    }
}

int SparseMatrix::get(int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        cout << "Posicion invalida: (" << xPos << "," << yPos << ")\n";
        return 0;
    }

    Node* cursor = start;
    cursor = cursor->getDown();
    while (cursor != start) {
        if (cursor->getY() == yPos) {
            break;
        }
        cursor = cursor->getDown();
    }

    if (cursor == start) {
        cout << "No hay valor en la posicion: (" << xPos << "," << yPos << ")\n";
        return 0;
    }
    
    Node* limite = cursor;
    cursor = cursor->getRight();
    while (cursor != limite) {
        if (cursor->getX() == xPos) {
            break;
        }
        cursor = cursor->getRight();
    }
    
    if (cursor == limite) {
        cout << "No hay valor en la posicion: (" << xPos << "," << yPos << ")" << endl;
        return 0;
    }

    return cursor->getValue();
}

void SparseMatrix::remove(int xPos, int yPos) {
    if (xPos < 0 || yPos < 0) {
        cout << "Posicion invalida: (" << xPos << "," << yPos << ")" << endl;
        return;
    }

    Node* cursor = start;
    cursor = cursor->getDown();
    while (cursor != start) {
        if (cursor->getY() == yPos) {
            break;
        }
        cursor = cursor->getDown();
    }
    if (cursor == start) {
        cout << "No hay valor en la posicion: (" << xPos << "," << yPos << ")\n";
        return;
    }
    
    Node* limite = cursor;
    cursor = cursor->getRight();
    while (cursor != limite) {
        if (cursor->getX() == xPos) {
            break;
        }
        cursor = cursor->getRight();
    }
    if (cursor == limite) {
        cout << "No hay valor en la posicion: (" << xPos << "," << yPos << ")" << endl;
        return;
    }

    Node* temp;
    
    temp = cursor->getUp();
    temp->setDown(cursor->getDown());
    cursor->getDown()->setUp(temp);

    temp = cursor->getLeft();
    temp->setRight(cursor->getRight());
    cursor->getRight()->setLeft(temp);

    delete cursor;

    //Eliminacion de centinelas si quedan vacíos
    //Centinela columna
    Node* centinelaX = start->getRight();
    while (centinelaX != start) {
        if (centinelaX->getDown() == centinelaX) {
            temp = centinelaX->getLeft();
            temp->setRight(centinelaX->getRight());
            centinelaX->getRight()->setLeft(temp);
            delete centinelaX;
            break;
        }
        centinelaX = centinelaX->getRight();
    }
    //Centinela fila
    Node* centinelaY = start->getDown();
    while (centinelaY != start) {
        if (centinelaY->getRight() == centinelaY) {
            temp = centinelaY->getUp();
            temp->setDown(centinelaY->getDown());
            centinelaY->getDown()->setUp(temp);
            delete centinelaY;
            break;
        }
        centinelaY = centinelaY->getDown();
    }
}

void SparseMatrix::printStoredValues() {
    Node* cursor = start;
    cursor = cursor->getDown();

    while (cursor != start){
        Node* limite = cursor;
        cursor = cursor->getRight();

        while (cursor != limite){
            cout << "(" << cursor->getX() << "," << cursor->getY() << ") --> " << cursor->getValue() << endl;
            cursor = cursor->getRight();
        }
        cursor = cursor->getDown();
    }
}

int SparseMatrix::density() {
    // Extremos (Se aprovecha el enlace circular)
    Node* cursorX = start->getLeft();
    Node* cursorY = start->getUp();

    int maxX = cursorX->getX();
    int maxY = cursorY->getY();

    if (maxX == -1 || maxY == -1) {
        cout << "La matriz esta vacia." << endl;
        return 0;
    } else {
        cout << "Dimensiones de la matriz: " << (maxX + 1) << " x " << (maxY + 1) << endl;
    }
    
    int total = (maxX + 1) * (maxY + 1); // +1 porque las posiciones empiezan en 0

    // Contador
    int cont = 0;
    Node* cursor = start;
    cursor = cursor->getDown();

    while (cursor != start){
        Node* limite = cursor;
        cursor = cursor->getRight();

        while (cursor != limite){
            cont++;
            cursor = cursor->getRight();
        }
        cursor = cursor->getDown();
    }

    // Evitar división por cero
    if (total == 0) {
        return 0;
    }
    return (cont * 100 / total);
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {

    // Verificación de dimensiones
    // Columnas de la primera
    Node* cursor = start->getLeft();
    int columnas = cursor->getX();

    // Filas de la segunda
    cursor = second->start->getUp();
    int filas = cursor->getY();

    if (columnas != filas) {
        cout << "Dimensiones incompatibles para multiplicacion: (" << columnas + 1 << " columnas, " << filas + 1 << " filas)" << endl;
        return nullptr;
    }
    // Si son compatibles, las dimensiones de la resultante serán:

    // Filas de la primera
    cursor = start->getUp();
    filas = cursor->getY();

    // Columnas de la segunda
    cursor = second->start->getLeft();
    columnas = cursor->getX();
    
    // Multiplicación
    SparseMatrix* result = new SparseMatrix();
    
    // Recorremos cada posición de la matriz resultante

    for (int fila = 0; fila <= filas; fila++) {
        for (int columna = 0; columna <= columnas; columna++) {

            // Buscamos la fila 
            Node* cursorFirst = start->getDown();
            while (cursorFirst != start) {
                if (cursorFirst->getY() == fila) {
                    break;
                }
                cursorFirst = cursorFirst->getDown();
            }

            // Buscamos la columna
            Node* cursorSecond = second->start->getRight();
            while (cursorSecond != second->start) {
                if (cursorSecond->getX() == columna) {
                    break;
                }
                cursorSecond = cursorSecond->getRight();
            }

            int sum = 0;

            // Multiplicamos los elementos correspondientes
            Node* tempFirst = cursorFirst->getRight();;
            while (tempFirst != cursorFirst) {
                Node* tempSecond = cursorSecond->getDown();
                while (tempSecond != cursorSecond) {
                    if (tempFirst->getX() == tempSecond->getY()) {
                        sum += tempFirst->getValue() * tempSecond->getValue();
                        break;
                    }
                    tempSecond = tempSecond->getDown();
                }
                tempFirst = tempFirst->getRight();
            }

            if (sum != 0) {
                result->add(sum, columna, fila);
            }
        }
    }

    return result;
}
