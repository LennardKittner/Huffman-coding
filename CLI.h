//
// Created by Lennard on 27.10.22.
//

#ifndef HUFFMAN_CLI_H
#define HUFFMAN_CLI_H

#include <string>
#include <vector>

enum Flag {
    HELP,
    OUT,
    IN,
    TREE,
    MODE,
    ERROR
};

struct Command {
    Flag type;
    std::string arg;
};

class CLI {
public:
    CLI(int, char**);
    std::vector<Command>* args;
private:
    int argc;
    char **argv;
    std::vector<Command>* parse();
    Command* parseCommand(const std::string&);
    Command* parseCommand(std::string, std::string);
};


#endif //HUFFMAN_CLI_H
