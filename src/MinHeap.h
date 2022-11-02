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
    std::shared_ptr<Node> pop();
    void insert(std::shared_ptr<Node>);
    std::shared_ptr<Node> min();
    unsigned long size();
private:
    std::vector<std::shared_ptr<Node>> heap;
    void bubbleUP(unsigned long);
    void bubbleDown(unsigned long);
};


#endif //HUFFMAN_MINHEAP_H
