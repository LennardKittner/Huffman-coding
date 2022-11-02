#include <iostream>
#include <fstream>
#include <vector>
#include "CLI.h"
#include "HuffmanCoder.h"

std::string help = "Options\n"
                   "  --help, -h        = Print help.\n"
                   "  --out, -o <file>  = Specify output file.\n"
                   "  --in, -i  <file>  = Specify input file.\n"
                   "  --encode, -en     = Encode the input file and write the compressed file to the output file.\n"
                   "  --decode, -de     = Decode the input file and write the decompressed file to the output file.\n";

//TODO: omit -i
int main(int argc, char *argv[]) {
    auto err = std::make_shared<int>(1);
    CLI cli(argc, argv);

    if (cli.args->count(HELP)) {
        std::cout << help;
        return 0;
    } else if (cli.args->count(ERROR)) {
        std::cout << "Huffman Error: Unknown argument '" << (*cli.args)[ERROR] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
        return *err;
    } else if (cli.args->count(ERRORFILE)) {
        std::cout << "Huffman Error: no such file or directory: '" << (*cli.args)[ERRORFILE] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
        return *err;
    }

    HuffmanCoder coder((*cli.args)[IN], err);
    if (*err == 1) {
        std::cout << "Huffman Error: could not read file: '" << (*cli.args)[IN] << "'" << std::endl;
        return *err;
    }

    if (cli.args->count(ENCODE)) {
        auto result = coder.encode();
        std::ofstream out((*cli.args)[OUT], std::ios::out | std::ios::binary);
        out.write((char*)&result->content[0], result->content.size() * sizeof(char));
        out.close();
    } else if (cli.args->count(DECODE)) {
        auto result = coder.decode();
        std::ofstream out((*cli.args)[OUT], std::ios::out | std::ios::binary);
        out.write(&(*result)[0], result->size() * sizeof(char));
        out.close();
    }

    return 0;
}
