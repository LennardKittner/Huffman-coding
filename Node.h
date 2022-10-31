//
// Created by Lennard Kittner on 10.03.18.
//

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H


#include <iostream>

struct Node {
    int count;
    char content;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};


#endif //HUFFMAN_NODE_H
