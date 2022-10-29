//
// Created by Lennard on 27.10.22.
//

#include "CLI.h"
#include <filesystem>

namespace fs = std::filesystem;

CLI::CLI(int argc, char *argv[]) {
    this->argc = argc;
    this->argv = argv;
    args = parse();
}


int CLI::parseCommand(char* args[], int len, std::vector<Command>* commands) {
    Command command = {ERROR, ""};
    int offset = 2;
    std::string arg1(args[0]);
    std::string arg2(len > 1 ? args[1] : "");
    fs::path arg2File(arg2);
    bool arg2Exists = len > 1 && fs::exists(arg2File);

    if (arg1 == "-h" || arg1 == "--help") {
        command.type = HELP;
        command.arg = arg2;
        offset = len;
    } else if (arg1 == "-o" || arg1 == "--out") {
        if (!arg2Exists) {
            command.type = ERRORFILE;
            command.arg = arg2;
            offset = len;
        } else {
            command.type = OUT;
            command.arg = arg2;
        }
    } else if (arg1 == "-i" || arg1 == "--in") {
        if (!arg2Exists) {
            command.type = ERRORFILE;
            command.arg = arg2;
            offset = len;
        } else {
            command.type = IN;
            command.arg = arg2;
        }
    } else if (arg1 == "-t" || arg1 == "--tree") {
        if (!arg2Exists) {
            command.type = ERRORFILE;
            command.arg = arg2;
            offset = len;
        } else {
            command.type = TREE;
            command.arg = arg2;
        }
    } else if (arg1 == "-en" || arg1 == "--encode") {
        command.type = ENCODE;
        command.arg = "";
        offset = 1;
    } else if (arg1 == "-de" || arg1 == "--decode") {
        command.type = DECODE;
        command.arg = "";
        offset = 1;
    } else {
        command.type = ERROR;
        command.arg = arg1 + " " + arg2;
        offset = len;
    }
    commands->push_back(command);

    return offset;
}

std::vector<Command>* CLI::parse() {
    auto* args = new std::vector<Command>();

    if (argc < 2) {
        Command command = {HELP, ""};
        args->push_back(command);
        return args;
    }

    int i = 1;
    while (i < argc) {
        i += parseCommand(argv+i, argc-i, args);
    }

    return args;
}