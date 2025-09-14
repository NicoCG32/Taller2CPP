#include "Node.h"
    
Node::Node(int value, int x, int y){
    this->value = value;
    this->x = x;
    this->y = y;
    this->right = nullptr;
    this->down = nullptr;
    this->left = nullptr;
    this->up = nullptr;
}

Node::~Node(){}

int Node::getValue(){
    return value;
}

int Node::getX(){
    return x;
}

int Node::getY(){
    return y;
}

Node* Node::getRight(){
    return right;
}

Node* Node::getDown(){
    return down;
}

Node* Node::getLeft(){
    return left;
}

Node* Node::getUp(){
    return up;
}

void Node::setValue(int value){
    this->value = value;
}

void Node::setX(int x){
    this->x = x;
}

void Node::setY(int y){
    this->y = y;
}

void Node::setRight(Node* right){
    this->right = right;
}

void Node::setDown(Node* down){
    this->down = down;
}

void Node::setLeft(Node* left){
    this->left = left;
}

void Node::setUp(Node* up){
    this->up = up;
}
