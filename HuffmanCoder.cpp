//
// Created by Lennard on 27.10.22.
//

#include "HuffmanCoder.h"
#include <string>
#include <fstream>
#include "Quicksorter.h"
#include "MinHeap.h"
#include <cmath>

namespace fs = std::filesystem;

HuffmanCoder::HuffmanCoder(std::string input, std::shared_ptr<int> err) {
    *err = 0;

    char byte = 0;
    std::ifstream input_file(input);
    if (!input_file.is_open()) {
        *err = 1;
    }
    while (input_file.get(byte)) {
        fileContent.push_back(byte);
    }
    input_file.close();
}

// builds the lookup table by traversing the tree
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

std::shared_ptr<std::map<char, BitMap>> HuffmanCoder::buildLookupTable(std::shared_ptr<Node> tree) {
    auto lookupTable = std::make_shared<std::map<char, BitMap>>();
    BitMap buff;
    traverseTree(tree, buff, lookupTable);
    return lookupTable;
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

    char sizeInBytes = std::ceil(std::log(max) / std::log(256)); // char is long enough
    char ignoreBytes = sizeof(int) - sizeInBytes;
    encodedHistogram->pushBack(sizeInBytes);
    encodedHistogram->pushBack((char) histogram.size());
    for (auto const &x : histogram) {
        encodedHistogram->pushBack(x.first);
        encodedHistogram->pushBack(x.second, ignoreBytes);
    }
    return encodedHistogram;
}

// appends the encoded Text to content. This avoids coping the buffer later.
void HuffmanCoder::appendEncodeText(const std::vector<unsigned char>& text, std::shared_ptr<BitMap> appendTo, std::shared_ptr<std::map<char, BitMap>> lookUpTable) {
    // The first byte contains the number of bits to ignore at the end.
    // This is required because the encoded text may not be 8bit aligned and so padding is added.
    appendTo->pushBack((char) 0);
    unsigned long paddingIndex = appendTo->content.size()-1;

    for (char curr : text) {
        appendTo->pushBack((*lookUpTable)[curr]);
    }
    appendTo->content[paddingIndex] = 8 - appendTo->count % 8;
}

std::shared_ptr<BitMap> HuffmanCoder::encode() {
    std::map<char, int> histogram;
    for (char curr : fileContent) {
        if (histogram.count(curr) == 0) {
            histogram[curr] = 0;
        }
        histogram[curr]++;
    }

    auto tree = generateTree(histogram);
    auto lookUpTable = buildLookupTable(tree);
    auto encodedHistogram = encodeHistogram(histogram);
    appendEncodeText(fileContent, encodedHistogram, lookUpTable);
    return encodedHistogram;
}

std::shared_ptr<std::map<char, int>> HuffmanCoder::decodeHistogram(const std::vector<unsigned char>& encodedContent, std::shared_ptr<int> endIndex) {
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

std::shared_ptr<std::string> HuffmanCoder::decodeText(std::shared_ptr<Node> tree, const std::vector<unsigned char>& encodedContent, int firstChar) {
    BitMap bitMap;
    bitMap.content = encodedContent;
    bitMap.count = encodedContent.size() * sizeof(char) * 8;
    auto result = std::make_shared<std::string>("");
    auto curr = tree;
    int paddingAtTheEnd = bitMap.content[firstChar];
    bitMap.count -= paddingAtTheEnd;

    for (int i = (firstChar+1) * sizeof(char) * 8; i < bitMap.count; i++) {
        curr = bitMap.get(i) ? curr->right : curr->left;
        if (curr->content != 0) {
            *result += curr->content;
            curr = tree;
        }
    }
    return result;
}

std::shared_ptr<std::string> HuffmanCoder::decode() {
    auto histogramEndIndex = std::make_shared<int>(0);
    auto histogram = decodeHistogram(fileContent, histogramEndIndex);
    auto tree = generateTree(*histogram);
    auto decodedText = decodeText(tree, fileContent, *histogramEndIndex);

    return decodedText;
}
