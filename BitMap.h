//
// Created by Lennard on 31.10.22.
//

#ifndef HUFFMAN_BITMAP_H
#define HUFFMAN_BITMAP_H

#include <vector>

class BitMap {
public:
    BitMap();
    BitMap(BitMap const&);
    void pushBack(bool);
    void pushBack(BitMap);
    char get(unsigned long);
    unsigned long count;
    std::vector<char> content;
};


#endif //HUFFMAN_BITMAP_H
