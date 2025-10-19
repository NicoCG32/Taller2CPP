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

    int getValue();
    int getX();
    int getY();
    Node* getRight();
    Node* getDown();
    Node* getLeft();
    Node* getUp();

    void setValue(int val);
    void setX(int x);
    void setY(int y);
    void setRight(Node* right);
    void setDown(Node* down);
    void setLeft(Node* left);
    void setUp(Node* up);
    
};

