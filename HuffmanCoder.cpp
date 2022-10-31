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

void HuffmanCoder::traverseTree(std::shared_ptr<Node> tree, BitMap buff, std::shared_ptr<std::map<char, BitMap>> result) {
    if (tree->content != 0) {
        (*result)[tree->content] = buff;
        return;
    }
    BitMap rightBuffer(buff);
    buff.pushBack(false);
    rightBuffer.pushBack(true);
    traverseTree(tree->left, buff, result);
    traverseTree(tree->right, rightBuffer, result);
}

std::shared_ptr<std::map<char, BitMap>> HuffmanCoder::buildLookUpTable(std::shared_ptr<Node> tree) {
    auto lookUpTable = std::make_shared<std::map<char, BitMap>>();
    BitMap buff;
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

std::shared_ptr<std::vector<char>> HuffmanCoder::encodeLookUpTable(std::shared_ptr<std::map<char, BitMap>> lookUpTable) {
    int max = -1;
    for (auto const &x : *lookUpTable) {
        if (x.second.count > max)
            max = x.second.count;
    }
    char byteSize = (max + 8 - 1) / 8; // This is a narrowing conversion but a Huffman code word should not be longer than 256 bytes
    // How long are the entries?
    auto encodedTable = std::make_shared<std::vector<char>>();
    encodedTable->push_back(byteSize);
    for (auto const &x : *lookUpTable) {
        encodedTable->push_back(x.first);
        for (int i = 0; i < x.second.content.size(); i++) {
            encodedTable->push_back(x.second.content[i]);
        }
        for (int i = 0; i < byteSize - x.second.content.size(); i++) {
            encodedTable->emplace_back(0);
        }
    }
}

std::shared_ptr<std::map<char, BitMap>> HuffmanCoder::decodeLookUpTable(std::shared_ptr<std::vector<char>>) {

}

std::shared_ptr<BitMap> HuffmanCoder::encodeText(std::string text, std::shared_ptr<std::map<char, BitMap>> lookUpTable) {
    auto encodedText = std::make_shared<BitMap>();
    for (char curr : text) {
        encodedText->pushBack((*lookUpTable)[curr]);
    }

    return encodedText;
}

int HuffmanCoder::encode() {
    std::string text;
    std::map<char, int> histogram;
    char byte = 0;

    std::ifstream input_file(input);
    if (!input_file.is_open()) {
        return 1;
    }

    while (input_file.get(byte)) {
        text.push_back(byte);
        if (histogram.count(byte) == 0) {
            histogram[byte] = 0;
        }
        histogram[byte]++;
    }
    input_file.close();

    auto tree = generateTree(histogram);
    auto lookUpTable = buildLookUpTable(tree);
    //auto encodedTable = encodeLookUpTable(lookUpTable);
    auto encodedText = encodeText(text, lookUpTable);

    std::ofstream out(output, std::ios::out | std::ios::binary | std::ios::app);

    out.write((char*)&encodedText->content[0], encodedText->content.size() * sizeof(char));

    out.close();
    return 0;
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
