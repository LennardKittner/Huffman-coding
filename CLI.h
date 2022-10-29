//
// Created by Lennard on 27.10.22.
//

#ifndef HUFFMAN_CLI_H
#define HUFFMAN_CLI_H

#include <string>
#include <map>

enum Flag {
    HELP,
    OUT,
    IN,
    TREE,
    ENCODE,
    DECODE,
    ERROR,
    ERRORFILE
};

class CLI {
public:
    CLI(int, char**);
    std::map<Flag, std::string>* args;
private:
    int argc;
    char **argv;
    std::map<Flag, std::string>* parse();
    int parseCommand(char*[],int , std::map<Flag, std::string>*);
};


#endif //HUFFMAN_CLI_H
