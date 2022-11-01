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

std::shared_ptr<BitMap> HuffmanCoder::encodeHistogram(const std::map<char, int>& histogram) {
    auto encodedHistogram = std::make_shared<BitMap>();
    int max = -1;
    for (auto const &x : histogram) {
        if (x.second > max)
            max = x.second;
    }
    // TODO: calc padding
    char sizeInBytes = sizeof(int); // char is long enough
    char ignoreBytes = sizeof(int) - sizeInBytes;
    encodedHistogram->pushBack(sizeInBytes);
    encodedHistogram->pushBack((char) histogram.size());
    for (auto const &x : histogram) {
        encodedHistogram->pushBack(x.first);
        encodedHistogram->pushBack(x.second, ignoreBytes);
    }
    return encodedHistogram;
}


std::shared_ptr<BitMap> HuffmanCoder::encodeText(std::string text, std::shared_ptr<std::map<char, BitMap>> lookUpTable) {
    auto encodedText = std::make_shared<BitMap>();
    //TODO: make dynamic
    encodedText->pushBack((char) 0);
    encodedText->pushBack((char) 0);
    encodedText->pushBack((char) 0);
    encodedText->pushBack((char) 0);

    for (char curr : text) {
        encodedText->pushBack((*lookUpTable)[curr]);
    }
    encodedText->content[0] = (encodedText->count >> 24) & 0xff;
    encodedText->content[1] = (encodedText->count >> 16) & 0xff;
    encodedText->content[2] = (encodedText->count >> 8) & 0xff;
    encodedText->content[3] = (encodedText->count >> 0) & 0xff;

    return encodedText;
}

//TODO: extract file read and write from encode
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
    auto encodedHistogram = encodeHistogram(histogram);
    auto encodedText = encodeText(text, lookUpTable);
    encodedHistogram->pushBack(*encodedText); //TODO: maybe do it in encodeText to avoid copying twice

    std::ofstream out(output, std::ios::out | std::ios::binary);

    out.write((char*)&encodedHistogram->content[0], encodedHistogram->content.size() * sizeof(char));

    out.close();
    return 0;
}

std::shared_ptr<std::map<char, int>> HuffmanCoder::decodeHistogram(const std::vector<char>& encodedContent, std::shared_ptr<int> endIndex) {
    char sizeInBytes = encodedContent[0];
    char length = encodedContent[1];
    auto histogram = std::make_shared<std::map<char, int>>();
    int curr = 2;
    for (char i = 0; i < length; i++) {
        char currentChar = encodedContent[curr];
        curr++;
        int count = 0;
        for (char j = 0; j < sizeInBytes; j++) {
            count += encodedContent[curr+j] << (((sizeInBytes-1) - j) * 8);
        }
        (*histogram)[currentChar] = count;
        curr += sizeInBytes;
    }
    *endIndex = curr;
    return histogram;
}

std::string HuffmanCoder::decodeText(std::shared_ptr<Node> tree, const std::vector<char>& encodedContent, std::shared_ptr<int> firstChar) {
    BitMap bitMap;
    bitMap.content = encodedContent;
    bitMap.count = encodedContent.size() * sizeof(char) * 8;
    std::string result = "";
    auto curr = tree;
    int i = *firstChar;
    //TODO: read dynamic
    int length = bitMap.content[i++] << 24;
    length += bitMap.content[i++] << 16;
    length += bitMap.content[i++] << 8;
    length += bitMap.content[i++];
    length += *firstChar * sizeof(char) * 8;

    for ( i *= sizeof(char) * 8; i < length; i++) {
        curr = bitMap.get(i) ? curr->right : curr->left;
        if (curr->content != 0) {
            result += curr->content;
            curr = tree;
        }
    }
    return result;
}

//TODO: extract file read and write from decode
int HuffmanCoder::decode() {
    std::string text;
    std::vector<char> encodedContent;
    char byte = 0;

    std::ifstream input_file(input);
    if (!input_file.is_open()) {
        return 1;
    }

    while (input_file.get(byte)) {
        encodedContent.push_back(byte);
    }
    input_file.close();

    auto histogramEndIndex = std::make_shared<int>(0);
    auto histogram = decodeHistogram(encodedContent, histogramEndIndex);
    auto tree = generateTree(*histogram);
    auto decodedText = decodeText(tree, encodedContent, histogramEndIndex);

    std::ofstream out(output, std::ios::out | std::ios::binary);

    out.write(&decodedText[0], decodedText.size() * sizeof(char));

    out.close();

    return 0;
}


