//
// Created by Lennard on 31.10.22.
//

#include "BitMap.h"

BitMap::BitMap() {
    this->count = 0;
}

BitMap::BitMap(BitMap const &copy) {
    this->content = std::vector<char>(copy.content);
    this->count = copy.count;
}

void BitMap::pushBack(bool bit) {
    if (count % 8 == 0)
        content.emplace_back(0);
    if (bit) {
        content[count / 8] += 1 << ((8 - count % 8) - 1);
    }
    count++;
}

void BitMap::pushBack(BitMap bitMap) {
    if (count % 8 == 0) {
        content.insert(content.end(), bitMap.content.begin(), bitMap.content.end());
        count += bitMap.count;
        return;
    }

    for (int i = 0; i < bitMap.count; i++) {
        pushBack(bitMap.get(i));
    }
}

char BitMap::get(unsigned long i) {
    char value = content[i / 8];
    value = value >> (7 - (i % 8));
    value = value & 1;
    return value;
}

