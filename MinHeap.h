//
// Created by Lennard on 30.10.22.
//

#ifndef HUFFMAN_MINHEAP_H
#define HUFFMAN_MINHEAP_H


#include "Node.h"
#include <vector>

class MinHeap {
public:
    MinHeap();
    Node pop();
    void insert(Node);
    Node min();
    unsigned long size();
private:
    std::vector<Node> heap;
    void bubbleUP(unsigned long);
    void bubbleDown(unsigned long);
};


#endif //HUFFMAN_MINHEAP_H
