//
// Created by Lennard Kittner on 10.03.18.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H


#include <iostream>

class Node {
public:
    void setValue0(int);
    void setValue1(int);
    void setNode0(Node);
    void setNode1(Node);
    int getValue0();
    int getValue1();
    Node* getNode0();
    Node* getNode1();
    void setValue(int);
    int getValue();
    int compareTo(Node);
    bool isSingleNode();
    Node(int);
    Node(Node*, Node*);

private:
    int value0;
    int value1;
    Node* node0;
    Node* node1;
    int value;
    bool singleNode = false;

};


#endif //HUFFMAN_NODE_H
