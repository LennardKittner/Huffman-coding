//
// Created by Lennard Kittner on 08.03.18.
//

#ifndef HUFFMAN_QUICKSORTER_H
#define HUFFMAN_QUICKSORTER_H


#include <vector>
#include "Node.h"

class Quicksorter {
    public:
        void sort(std::vector<int>*);
        void sort(std::vector<int>*,int ,int );
        void sort(std::vector<Node*>*);
        void sort(std::vector<Node*>*,int ,int );
        ~Quicksorter();

    private:
        int partition(std::vector<int>*,int ,int );
        int partition(std::vector<Node*>*,int ,int );


};


#endif //HUFFMAN_QUICKSORTER_H
