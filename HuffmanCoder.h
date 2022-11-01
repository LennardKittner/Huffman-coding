//
// Created by Lennard on 27.10.22.
//

#ifndef HUFFMAN_HUFFMANCODER_H
#define HUFFMAN_HUFFMANCODER_H

#include <map>
#include <vector>
#include "Node.h"
#include "BitMap.h"

class HuffmanCoder {
public:
    int encode();
    int decode();
    HuffmanCoder(std::string, std::string, std::string);

private:
    std::string input;
    std::string output;
    std::string treePath;
    std::map<char, std::vector<char>> result;
    std::map<std::string, char> resultRev;
    std::map<std::string, int> binary;
    std::shared_ptr<Node> generateTree(const std::map<char, int>& map);
    std::shared_ptr<std::map<char, BitMap>> buildLookUpTable(std::shared_ptr<Node>);
    void traverseTree(std::shared_ptr<Node>, BitMap, std::shared_ptr<std::map<char, BitMap>>);
    std::shared_ptr<BitMap> encodeHistogram(const std::map<char, int>&);
    std::shared_ptr<std::map<char, int>> decodeHistogram(const std::vector<char>&, std::shared_ptr<int>);
    std::shared_ptr<BitMap> encodeText(std::string ,std::shared_ptr<std::map<char, BitMap>>);
    std::string decodeText(std::shared_ptr<Node>, const std::vector<char>&, std::shared_ptr<int>);
};



#endif //HUFFMAN_HUFFMANCODER_H
