cmake_minimum_required(VERSION 3.8)
project(Huffman)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/Node.h src/CLI.cpp src/CLI.h src/HuffmanCoder.cpp src/HuffmanCoder.h src/MinHeap.cpp src/MinHeap.h src/BitMap.cpp src/BitMap.h)
add_executable(huffman ${SOURCE_FILES})

# Testing
include(CTest)
ENABLE_TESTING()

set(SOURCE_FILES_TEST src/Node.h src/CLI.cpp src/CLI.h src/HuffmanCoder.cpp src/HuffmanCoder.h src/MinHeap.cpp src/MinHeap.h src/BitMap.cpp src/BitMap.h)
add_executable(EncodeDecodeTest test/EncodeDecodeTest.cpp ${SOURCE_FILES_TEST})

add_test(EncodeDecodeTest EncodeDecodeTest)
