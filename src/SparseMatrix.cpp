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
        std::cout << "No se pueden agregar valores cero.\n";
        return;
    }

    // Verificación, posiciones negativas no son válidas
    if (xPos < 0 || yPos < 0) {
        std::cout << "Posiciones inválidas: (" << xPos << "," << yPos << ")\n";
        return;
    }

    int x = -1;
    int y = -1;

    // Verificación, no existe ya un valor en la posición
    Node* tempX = start;
    Node* SentinelaX;
    while (x < xPos) {
        if (tempX->getRight() == start) {
            SentinelaX = new Node(0, x, -1);

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
            SentinelaY = new Node(0, -1, y);

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
    return 0;
}

void SparseMatrix::remove(int xPos, int yPos) {}

void SparseMatrix::printStoredValues() {
    Node* cursor = start;
    
    while (cursor->getDown() != start){
        cursor = cursor->getDown();
        Node* limite = cursor;
        while (cursor->getRight() != limite){
            cursor = cursor->getRight();
            if (cursor->getX() != -1 && cursor->getY() != -1) {
                cout << "(" << cursor->getX() << ", " << cursor->getY() << ") --> " << cursor->getValue() << endl;
            }
        }
    }
}

int SparseMatrix::density() {
    return 0;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second) {
    return nullptr;
}

