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

SparseMatrix::~SparseMatrix() {}

void SparseMatrix::add(int value, int xPos, int yPos) {

    // Verificación, valor cero no es válido CREO (no tendría sentido almacenar ceros)
    if (value == 0) {
    cout << "No se pueden agregar valores cero.\n";
        return;
    }

    // Verificación, posiciones negativas no son válidas
    if (xPos < 0 || yPos < 0) {
    cout << "Posiciones inválidas: (" << xPos << "," << yPos << ")\n";
        return;
    }

    int x = -1;
    int y = -1;

    // Verificación, no existe ya un valor en la posición
    Node* tempX = start;
    Node* SentinelaX;
    while (x < xPos) {
        if (tempX->getRight() == start) {
            SentinelaX = new Node(0, x + 1, -1);

            tempX->setRight(SentinelaX);
            SentinelaX->setLeft(tempX);

            SentinelaX->setRight(start);
            start->setLeft(SentinelaX);

            SentinelaX->setUp(SentinelaX);
            SentinelaX->setDown(SentinelaX);

            tempX = SentinelaX;
        } else {
            tempX = tempX->getRight();
        }
        x++;
    }
    SentinelaX = tempX;

    Node* tempY = start;
    Node* SentinelaY;
    while (y < yPos) {
        if (tempY->getDown() == start) {
            SentinelaY = new Node(0, -1, y + 1);

            tempY->setDown(SentinelaY);
            SentinelaY->setUp(tempY);

            SentinelaY->setDown(start);
            start->setUp(SentinelaY);

            SentinelaY->setRight(SentinelaY);
            SentinelaY->setLeft(SentinelaY);

            tempY = SentinelaY;
        } else {
            tempY = tempY->getDown();
        }
        y++;
    }
    SentinelaY = tempY;

    tempX = SentinelaX->getDown();
    while (tempX->getY() != -1 && tempX->getY() < yPos) {
        tempX = tempX->getDown();
    }
    tempY = SentinelaY->getRight();
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

    if (SentinelaX->getDown() == SentinelaX) {
        SentinelaX->setDown(newNode);
        newNode->setUp(SentinelaX);
        SentinelaX->setUp(newNode);
        newNode->setDown(SentinelaX);

    } else {
        tempX = SentinelaX->getDown();
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

    if (SentinelaY->getRight() == SentinelaY) {
        SentinelaY->setRight(newNode);
        newNode->setLeft(SentinelaY);
        SentinelaY->setLeft(newNode);
        newNode->setRight(SentinelaY);

    } else {
        tempY = SentinelaY->getRight();
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
        return INT32_MAX;
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
}

void SparseMatrix::printStoredValues() {
    Node* cursor = start;
    cursor = cursor->getDown();

    while (cursor != start){
        Node* limite = cursor;
        cursor = cursor->getRight();

        while (cursor != limite){
            cout << "(" << cursor->getX() << ", " << cursor->getY() << ") --> " << cursor->getValue() << endl;
            cursor = cursor->getRight();
        }
        cursor = cursor->getDown();
    }
}

int SparseMatrix::density() {
     // Extremos
    Node* cursorX = start->getLeft();
    Node* cursorY = start->getUp();

    int maxX = cursorX->getX();
    int maxY = cursorY->getY();

    while (cursorX->getDown() == cursorX || cursorY->getRight() == cursorY) {
        if (cursorX->getDown() == cursorX) {
            cursorX = cursorX->getLeft();
            maxX = cursorX->getX();
        }
        if (cursorY->getRight() == cursorY) {
            cursorY = cursorY->getUp();
            maxY = cursorY->getY();
        }
    }

    cout << "Dimensiones de la matriz: " << (maxX + 1) << " x " << (maxY + 1) << endl;
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
    return nullptr;
}

