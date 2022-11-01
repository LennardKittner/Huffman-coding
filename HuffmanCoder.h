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
    std::shared_ptr<BitMap> encode();
    std::shared_ptr<std::string> decode();
    HuffmanCoder(std::string, std::string, std::shared_ptr<int>);

private:
    std::string treePath;
    std::vector<char> fileContent;
    std::shared_ptr<Node> generateTree(const std::map<char, int>& map);
    std::shared_ptr<std::map<char, BitMap>> buildLookupTable(std::shared_ptr<Node> tree);
    void traverseTree(std::shared_ptr<Node>, BitMap, std::shared_ptr<std::map<char, BitMap>>);
    std::shared_ptr<BitMap> encodeHistogram(const std::map<char, int>&);
    std::shared_ptr<std::map<char, int>> decodeHistogram(const std::vector<char>&, std::shared_ptr<int>);
    void appendEncodeText(const std::vector<char>&, std::shared_ptr<BitMap>, std::shared_ptr<std::map<char, BitMap>>);
    std::shared_ptr<std::string> decodeText(std::shared_ptr<Node>, const std::vector<char>&, int);
};



#endif //HUFFMAN_HUFFMANCODER_H
