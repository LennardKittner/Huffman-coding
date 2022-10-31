//
// Created by Lennard on 27.10.22.
//

#include "CLI.h"
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

CLI::CLI(int argc, char *argv[]) {
    this->argc = argc;
    this->argv = argv;
    args = parse();
    if (args->count(OUT) == 0) {
        (*args)[OUT] = "./out.huff";
    }
    if (args->count(TREE) == 0) {
        (*args)[TREE] = "";
    }
    if (args->count(ENCODE) == 0 && args->count(DECODE) == 0) {
        (*args)[ENCODE] = "";
    }
}

int CLI::parseCommand(char* arguments[], int len, std::shared_ptr<std::map<Flag, std::string>> commands) {
    Flag flag;
    int offset = 2;
    std::string arg1(arguments[0]);
    std::string arg2(len > 1 ? arguments[1] : "");
    fs::path arg2File(arg2);
    bool arg2Exists = len > 1 && fs::exists(arg2File);

    if (arg1 == "-h" || arg1 == "--help") {
        flag = HELP;
        arg2 = "";
        offset = len;
    } else if (arg1 == "-o" || arg1 == "--out") {
        flag = OUT;
    } else if (arg1 == "-i" || arg1 == "--in") {
        if (!arg2Exists) {
            flag = ERRORFILE;
            offset = len;
        } else {
            flag = IN;
        }
    } else if (arg1 == "-t" || arg1 == "--tree") {
        if (!arg2Exists) {
            flag = ERRORFILE;
            offset = len;
        } else {
            flag = TREE;
        }
    } else if (arg1 == "-en" || arg1 == "--encode") {
        flag = ENCODE;
        arg2 = "";
        offset = 1;
    } else if (arg1 == "-de" || arg1 == "--decode") {
        flag = DECODE;
        arg2 = "";
        offset = 1;
    } else {
        flag = ERROR;
        arg2 = arg1 + " " + arg2;
        offset = len;
    }
    (*commands)[flag] = arg2;

    return offset;
}

std::shared_ptr<std::map<Flag, std::string>> CLI::parse() {
    auto commands = std::make_shared<std::map<Flag, std::string>>();

    if (argc < 2) {
        (*commands)[HELP] = "";
        return commands;
    }

    int i = 1;
    while (i < argc) {
        i += parseCommand(argv+i, argc-i, commands);
    }

    return commands;
}