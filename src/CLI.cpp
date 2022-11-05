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
}

int CLI::parseCommand(char* arguments[], std::shared_ptr<std::map<Flag, std::string>> commands) {
    Flag flag;
    std::string arg(arguments[0]);
    fs::path argFile(arg);
    bool argExists = fs::exists(argFile);
    int retCode = 0;

    if (arg == "-h" || arg == "--help") {
        flag = HELP;
        retCode = 1;
    } else if (arg == "-en" || arg == "--encode") {
        flag = ENCODE;
    } else if (arg == "-de" || arg == "--decode") {
        flag = DECODE;
    } else if (arg[0] == '-') {
        flag = ERROR;
        retCode = 2;
    } else if (commands->count(IN)) {
        flag = OUT;
    } else if (!commands->count(IN)) {
        if (!argExists) {
            flag = ERRORFILE;
            retCode = 3;
        } else {
            flag = IN;
        }
    } else {
        flag = ERROR;
        retCode = 4;
    }
    (*commands)[flag] = arg;
    return retCode;
}

std::shared_ptr<std::map<Flag, std::string>> CLI::parse() {
    auto commands = std::make_shared<std::map<Flag, std::string>>();

    if (argc < 2) {
        (*commands)[HELP] = "";
        return commands;
    }

    for (int i = 1; i < argc; i++) {
        if (parseCommand(argv+i, commands) != 0) {
            break;
        }
    }

    if (commands->count(HELP) || commands->count(ERROR) || commands->count(ERRORFILE)) {
        return commands;
    }
    if (commands->count(OUT) == 0) {
        (*commands)[OUT] = "./out.huff";
    }
    if (commands->count(ENCODE) == 0 && commands->count(DECODE) == 0) {
        (*commands)[ENCODE] = "";
    }
    return commands;
}