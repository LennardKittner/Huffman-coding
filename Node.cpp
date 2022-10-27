//
// Created by Lennard Kittner on 10.03.18.
//

#include "Node.h"

Node::Node(int value0){
    this->value0 = value0;
    this->value1 = 0;
    this->singleNode = true;
    value = value0;
}
Node::Node(Node* node0, Node* node1){
    this->node0 = node0;
    this->node1 = node1;
    value = node0->getValue()+node1->getValue();
}

void Node::setValue0(int value0){
    this->value0 = value0;
}
void Node::setValue1(int value1){
    this->value1 = value1;
}
void Node::setNode0(Node node0){
    this->node0 = &node0;
}
void Node::setNode1(Node node1){
    this->node1 = &node1;
}
int Node::getValue0(){
    return value0;
}
int Node::getValue1(){
    return value1;
}
Node* Node::getNode0(){
    return node0;
}
Node* Node::getNode1(){
    return node1;
}
void Node::setValue(int value){
    this->value = value;
}
int Node::getValue(){
    return value;
}
int Node::compareTo(Node n){
    return getValue()-n.getValue();
}
bool Node::isSingleNode(){
    return singleNode;
}