#include <iostream>
#include <fstream>
#include <vector>
#include "CLI.h"
#include "HuffmanCoder.h"

std::string help = "Usage\n\n"
                   "  huffman [options]  <path-to-source>  <path-to-target>\n"
                   "  huffman [options]  <path-to-source> \n\n"
                   "  Specify a source file to encode / decode it and write the result to the target path.\n"
                   "  If not specified the target path will be set to \"./out.huff\". By default the \"-en\" option is set.\n\n"

                   "Options\n"
                   "  --help,   -h      = Print help.\n"
                   "  --encode, -en     = Encode the input file and write the compressed file to the output file.\n"
                   "  --decode, -de     = Decode the input file and write the decompressed file to the output file.\n";

int main(int argc, char *argv[]) {
    auto err = std::make_shared<int>(SUCCESS);
    CLI cli(argc, argv);

    if (cli.args->count(HELP)) {
        std::cout << help;
        return SUCCESS;
    } else if (cli.args->count(ERROR)) {
        std::cout << "Huffman Error: Unknown argument '" << (*cli.args)[ERROR] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
        return FILE_ERROR;
    } else if (cli.args->count(ERRORFILE)) {
        std::cout << "Huffman Error: no such file or directory: '" << (*cli.args)[ERRORFILE] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
        return FILE_ERROR;
    }

    HuffmanCoder coder((*cli.args)[IN], err);
    if (*err == FILE_ERROR) {
        std::cout << "Huffman Error: could not read file: '" << (*cli.args)[IN] << "'" << std::endl;
        return *err;
    }

    if (cli.args->count(ENCODE)) {
        auto result = coder.encode();
        std::ofstream out((*cli.args)[OUT], std::ios::out | std::ios::binary);
        out.write((char*)&result->content[0], result->content.size() * sizeof(char));
        out.close();
        if (!out) {
            std::cout << "Huffman Error: The result could not be written to disk."<< std::endl;
            return FILE_ERROR;
        }
    } else if (cli.args->count(DECODE)) {
        auto result = coder.decode(err);
        switch (*err) {
            case HISTOGRAM_ERROR:
                std::cout << "Huffman Error: The tree could not be built because the file is corrupted."<< std::endl;
                return *err;
            case TEXT_ERROR:
                std::cout << "Huffman Error: The text could not be decoded because the file is corrupted."<< std::endl;
                break;
        }
        std::ofstream out((*cli.args)[OUT], std::ios::out | std::ios::binary);
        out.write(&(*result)[0], result->size() * sizeof(char));
        out.close();
        if (!out) {
            std::cout << "Huffman Error: The result could not be written to disk."<< std::endl;
            return FILE_ERROR;
        }
    }

    return 0;
}
