cmake_minimum_required(VERSION 3.8)
project(Huffman)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Node.h CLI.cpp CLI.h HuffmanCoder.cpp HuffmanCoder.h MinHeap.cpp MinHeap.h BitMap.cpp BitMap.h)
add_executable(Huffman ${SOURCE_FILES})