#include <iostream>
#include <fstream>
#include <vector>
#include "CLI.h"
#include "HuffmanCoder.h"

std::string help = "Options\n"
                   "  --help, -h        = Print help.\n"
                   "  --out, -o <file>  = Specify output file.\n"
                   "  --in, -i  <file>  = Specify input file.\n"
                   "  --tree, -t <file> = Specify the huffman tree file.\n"
                   "  --encode, -en     = Encode the input file and write the compressed file to the output file.\n"
                   "  --decode, -de     = Decode the input file and write the decompressed file to the output file.\n";

//TODO: remove pointer and use smart pointer instead
//TODO: set up git actions
int main(int argc, char *argv[]) {
    CLI cli(argc, argv);

    if (cli.args->count(HELP)) {
        std::cout << help;
    } else if (cli.args->count(ERROR)) {
        std::cout << "Huffman Error: Unknown argument '" << (*cli.args)[ERROR] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
    } else if (cli.args->count(ERRORFILE)) {
        std::cout << "Huffman Error: no such file or directory: '" << (*cli.args)[ERRORFILE] << "'" << std::endl;
        std::cout << "Huffman Error: Run 'huffman --help' for all supported options." << std::endl;
    }

    HuffmanCoder coder((*cli.args)[IN], (*cli.args)[OUT], (*cli.args)[TREE]);

    if (cli.args->count(ENCODE)) {
        coder.encode();
    } else if (cli.args->count(DECODE)) {
        coder.decode();
    }

    return 0;
}
