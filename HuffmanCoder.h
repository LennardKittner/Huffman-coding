//
// Created by Lennard on 27.10.22.
//

#ifndef HUFFMAN_HUFFMANCODER_H
#define HUFFMAN_HUFFMANCODER_H

#include <map>
#include <vector>
#include "Node.h"

class HuffmanCoder {
public:
    int encode();
    int decode();
    HuffmanCoder(std::string, std::string, std::string);

private:
    std::string input;
    std::string output;
    std::string tree;
    std::map<char, std::string> result;
    std::map<std::string, char> resultRev;
    std::map<std::string, int> binary;
    std::vector<int> times;
    void processNode(std::string, std::shared_ptr<Node>);
    void generateTree(std::map<char, int> map);
    void merge(bool a,std::map<char, int> map);

};


#endif //HUFFMAN_HUFFMANCODER_H
