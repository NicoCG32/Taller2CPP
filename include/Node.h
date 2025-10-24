#pragma once

class Node {

private:
    int value;
    int x;
    int y;
    Node* right;
    Node* down;
    Node* left;
    Node* up;

public:
    Node(int val, int x, int y);
    ~Node();

    /** Obtiene el valor almacenado en el nodo. 
     * @return int Valor almacenado en el nodo.
    */
    int getValue();

    /** Obtiene la coordenada X del nodo. 
     * @return int Coordenada X del nodo.
    */
    int getX();

    /** Obtiene la coordenada Y del nodo. 
     * @return int Coordenada Y del nodo.
    */
    int getY();

    /** Obtiene el puntero al nodo a la derecha. 
     * @return Node* Puntero al nodo a la derecha.
    */
    Node* getRight();

    /** Obtiene el puntero al nodo hacia abajo. 
     * @return Node* Puntero al nodo hacia abajo.
    */
    Node* getDown();

    /** Obtiene el puntero al nodo a la izquierda. 
     * @return Node* Puntero al nodo a la izquierda.
    */
    Node* getLeft();

    /** Obtiene el puntero al nodo hacia arriba. 
     * @return Node* Puntero al nodo hacia arriba.
    */
    Node* getUp();

    /** Establece el valor almacenado en el nodo. 
    * @param val Nuevo valor a almacenar en el nodo.
    */
    void setValue(int val);

    /** Establece el puntero al nodo a la derecha. 
     * @param right Puntero al nuevo nodo a la derecha.
    */
    void setRight(Node* right);

    /** Establece el puntero al nodo hacia abajo. 
     * @param down Puntero al nuevo nodo hacia abajo.
    */
    void setDown(Node* down);

    /** Establece el puntero al nodo a la izquierda. 
     * @param left Puntero al nuevo nodo a la izquierda.
    */
    void setLeft(Node* left);

    /** Establece el puntero al nodo hacia arriba. 
     * @param up Puntero al nuevo nodo hacia arriba.
    */
    void setUp(Node* up);
};

