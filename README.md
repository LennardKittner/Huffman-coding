# Huffman-coding
A CLI app to compress files using Huffman coding, the goal of this project was to learn C++ and Github actions, not to create the most efficient or fastest Huffman-coding algorithm.

## Usage
`huffman [options]  \<path-to-source\>  \<path-to-target\>`

`huffman [options]  \<path-to-source\>`

Specify a source file to encode / decode it and write the result to the target path.
If not specified the target path will be set to "./out.huff". By default the "-en" option is set.

**Options**

  `--help,   -h`      = Print help.

  `--encode, -en`     = Encode the input file and write the compressed file to the output file.

  `--decode, -de`     = Decode the input file and write the decompressed file to the output file.

## Requirements
The project has been tested on macOS and Linux.

## Compilation
To compile the project you will need `cmake` and `make`.

After cloning the repository navigate to the root directory of the repository and run
```
mkdir build
cd build
cmake ..
make huffman
```
After that you will find the huffman executable inside the build directory.

## Binary File format
In this section I will outline how the encoded binary files are structured.

|Byte:     | $0$                   | $1$                     | $2$      | $3$       | $HL \cdot (1 + SIB)$ |
|:---------|:----------------------|:------------------------|:---------|:----------|:---------------------|
|**Data:** | size in Bytes $(SIB)$ | histogram length $(HL)$ | checksum | histogram | encoded text         |

**size in Bytes $(SIB)$**: The number of bytes used to encode the character count.

**histogram length $(HL)$**: The number of characters contained in the histogram.

**checksum**: A checksum to validate the histogram.

**histogram**: The histogram contains a list of all the characters and how often they appear in the original text.

**encoded text**: The original text encoded using the generated huffman tree.