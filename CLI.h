//
// Created by Lennard on 27.10.22.
//

#ifndef HUFFMAN_CLI_H
#define HUFFMAN_CLI_H


class CLI {
public:
    CLI(int, char**);
private:
    int argc;
    char **argv;
    void parse(int, char**);
};


#endif //HUFFMAN_CLI_H
