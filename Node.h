//
// Created by Lennard Kittner on 10.03.18.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H


#include <iostream>

class Node {
public:
    void setValue0(int value0){
        this->value0 = value0;
    }
    void setValue1(int value1){
        this->value1 = value1;
    }
    void setNode0(Node node0){
        this->node0 = &node0;
    }
    void setNode1(Node node1){
        this->node1 = &node1;
    }
    int getValue0(){
        return value0;
    }
    int getValue1(){
        return value1;
    }
    Node* getNode0(){
        return node0;
    }
    Node* getNode1(){
        return node1;
    }
    void setValue(int value){
        this->value = value;
    }
    int getValue(){
        return value;
    }
    int compareTo(Node n){
        return getValue()-n.getValue();
    }
    bool isSingleNode(){
        return singleNode;
    }
    Node(int value0){
        this->value0 = value0;
        this->value1 = 0;
        this->singleNode = true;
        value = value0;
    }
    Node(Node* node0, Node* node1){
        this->node0 = node0;
        this->node1 = node1;
        value = node0->getValue()+node1->getValue();
    }

private:
    int value0;
    int value1;
    Node* node0;
    Node* node1;
    int value;
    bool singleNode = false;

};


#endif //HUFFMAN_NODE_H
