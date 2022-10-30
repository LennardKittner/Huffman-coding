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
    void setNode0(std::shared_ptr<Node>);
    void setNode1(std::shared_ptr<Node>);
    int getValue0();
    int getValue1();
    std::shared_ptr<Node> getNode0();
    std::shared_ptr<Node> getNode1();
    void setValue(int);
    int getValue();
    int compareTo(Node);
    bool isSingleNode();
    Node(int);
    Node(std::shared_ptr<Node>, std::shared_ptr<Node>);

private:
    int value0;
    int value1;
    std::shared_ptr<Node> node0;
    std::shared_ptr<Node> node1;
    int value;
    bool singleNode = false;

};


#endif //HUFFMAN_NODE_H
