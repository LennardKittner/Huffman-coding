//
// Created by Lennard on 27.10.22.
//

#include "HuffmanCoder.h"
#include <string>
#include <fstream>
#include "Quicksorter.h"
#include "MinHeap.h"

namespace fs = std::filesystem;

HuffmanCoder::HuffmanCoder(std::string input, std::string output, std::string tree) {
    this->input = input;
    this->output = output;
    this->treePath = tree;
}

void HuffmanCoder::traverseTree(std::shared_ptr<Node> tree, std::vector<char> buff, std::shared_ptr<std::map<char, std::vector<char>>> result) {
    if (tree->content != 0) {
        (*result)[tree->content] = buff;
        return;
    }
    std::vector<char> rightBuffer(buff);
    buff.push_back(0);
    rightBuffer.push_back(1);
    traverseTree(tree->left, buff, result);
    traverseTree(tree->right, rightBuffer, result);
}

std::shared_ptr<std::map<char, std::vector<char>>> HuffmanCoder::buildLookUpTable(std::shared_ptr<Node> tree) {
    auto lookUpTable = std::make_shared<std::map<char, std::vector<char>>>();
    std::vector<char> buff;
    traverseTree(tree, buff, lookUpTable);
    return lookUpTable;
}

std::shared_ptr<Node> HuffmanCoder::generateTree(const std::map<char, int>& histogram) {
    MinHeap minHeap;
    for (auto const &x : histogram) {
        auto node = std::make_shared<Node>(x.second, x.first);
        minHeap.insert(node);
    }

    while (minHeap.size() > 1) {
        auto min1 = minHeap.pop();
        auto min2 = minHeap.pop();
        auto newNode = std::make_shared<Node>(min1->count + min2->count, 0, min1, min2);
        minHeap.insert(newNode);
    }
    return minHeap.pop();
}

int HuffmanCoder::encode() {
    std::vector<char> chars;
    std::map<char, int> histogram;
    char byte = 0;

    std::ifstream input_file(input);
    if (!input_file.is_open()) {
        return 1;
    }

    while (input_file.get(byte)) {
        chars.push_back(byte);
        if (histogram.count(byte) == 0) {
            histogram[byte] = 0;
        }
        histogram[byte]++;
    }
    input_file.close();

    auto tree = generateTree(histogram);
    auto lookUpTable = buildLookUpTable(tree);
    /*
    bool pedding_2B = false;
    std::string binaryStrTree = "";
    if (times[times.size()-1]>255)
        pedding_2B = true;

    std::vector<std::bitset<8>> binaryTree;
    for (auto const &x : map){
        binaryTree.push_back(std::bitset<8>((int)x.first));
        if (pedding_2B) {
            std::string tmp = toBinary(x.second, pedding_2B);
            binaryTree.push_back(std::bitset<8>(tmp.substr(0, 8)));
            binaryTree.push_back(std::bitset<8>(tmp.substr(8, 15)));
        }
        else
            binaryTree.push_back(std::bitset<8>(toBinary(x.second, pedding_2B)));
    }
    binaryTree.push_back(std::bitset<8>(0));
    if (!pedding_2B)
        binaryTree.push_back(std::bitset<8>(0));
    else {
        binaryTree.push_back(std::bitset<8>(0));
        binaryTree.push_back(std::bitset<8>(0));
    }

    int p = 8-binaryStr.size()%8;
    for (int i = 0;i < p;i++)
        binaryStr = binaryStr+"0";

    std::vector<std::bitset<8>> bstxt;
    for (int i = 0;i < binaryStr.size();i = i+8)
        bstxt.push_back(std::bitset<8>(binaryStr.substr(i,8)));

    std::ofstream output(filename+".huff"+ (pedding_2B ? "16" : "8"),std::ios::out | std::ios::binary | std::ios::app);

    for (int i = 0;i < binaryTree.size();i++) {
        output.write((char*)&binaryTree[i],sizeof(char));
    }

    for (int i = 0;i < bstxt.size();i++) {
        output.write((char*)&bstxt[i],sizeof(char));
    }
    output.close();
    std::cout << "finished\n";
    return 0;
     */
}

int HuffmanCoder::decode() {
    /*
    std::string filename;
    std::ifstream file;
    getline(std::cin, filename);
    file.open(filename, std::ios::binary);

    if (!file.is_open())
        return 1;
    std::string binary;
    char c;
    while (file.get(c)) {
        for (int i = 7; i >= 0; i--)
            binary += ((c >> i) & 1) == 1 ? "1" : "0";
    }

    int pedding = filename.substr(filename.find_last_of(".huff")+1,1) == "8" ? 8 : 16;

    int l =0;
    std::map<char, int> map;
    int till = pedding+8;
    for (int i = 0;pedding == 8 ? binary.substr(i, pedding+8) != "0000000000000000" : binary.substr(i, pedding+8) != "000000000000000000000000";i=i+pedding+8) {
        char cc = (char)getDezimal(binary.substr(i,8));
        int times = getDezimal(binary.substr(i+8, pedding));
        l += times;
        map[cc] = times;
        till = till+pedding+8;
    }

    std::string binarytxt = binary.substr(till,binary.size()-till-1);
    std::string resulttxt = "";

    generateTree(map);

    merge(false, map);

    std::string str = "";

    for (int i = 0;i < binarytxt.size();i++){
        str += binarytxt[i];

        if (resultrev.count(str) == 1) {
            resulttxt += resultrev[str];
            if (l == resulttxt.size())
                break;
            str = "";
        }
    }

    std::ofstream output;
    output.open(filename.substr(0,filename.find_last_of(".")));
    output << resulttxt;
    output.close();

    std::cout << "finished\n";
    return 0;
     */
}
