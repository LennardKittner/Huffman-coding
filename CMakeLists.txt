cmake_minimum_required(VERSION 3.8)
project(Huffman)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/Node.h src/CLI.cpp src/CLI.h src/HuffmanCoder.cpp src/HuffmanCoder.h src/MinHeap.cpp src/MinHeap.h src/BitMap.cpp src/BitMap.h)
add_executable(Huffman ${SOURCE_FILES})

include(CTest)
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)