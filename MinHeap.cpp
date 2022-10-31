//
// Created by Lennard on 30.10.22.
//

#include "MinHeap.h"

MinHeap::MinHeap() {
    heap.push_back({-1}); // Dummy element
}

void MinHeap::bubbleUP(unsigned long curr) {
    if (heap[curr].count > heap[curr/2].count) {
        return;
    }

    auto parent = heap[curr/2];
    heap[curr/2] = heap[curr];
    heap[curr] = parent;
    bubbleUP(curr/2);
}

void MinHeap::bubbleDown(unsigned long curr) {
    unsigned long swapWith = curr;
    if (curr * 2 < heap.size()-1 && heap[curr].count > heap[curr * 2].count) {
        swapWith = curr * 2;
    }
    if (curr * 2 + 1 < heap.size()-1 && heap[swapWith].count > heap[curr * 2 + 1].count) {
        swapWith = curr * 2 + 1;
    }
    if (swapWith == curr)
        return;
    auto smallerChild = heap[swapWith];
    heap[swapWith] = heap[curr];
    heap[curr] = smallerChild;
    bubbleDown(swapWith);
}

unsigned long MinHeap::size() {
    return heap.size()-1;
}

Node MinHeap::min() {
    if (size() == 0)
        return heap[0];
    return heap[1];
}

Node MinHeap::pop() {
    if (size() == 0) {
        return heap[0];
    }
    auto oldMin = heap[1];
    heap[1] = heap.back();
    heap.pop_back();
    bubbleDown(1);
    return oldMin;
}

void MinHeap::insert(Node node) {
    heap.push_back(node);
    bubbleUP(heap.size()-1);
}