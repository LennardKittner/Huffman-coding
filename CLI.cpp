//
// Created by Lennard on 27.10.22.
//

#include "CLI.h"

CLI::CLI(int argc, char *argv[]) {
    this->argc = argc;
    this->argv = argv;
    args = parse();
}

Command* CLI::parseCommand(const std::string& arg1) {
    Command* command = new Command();

    if (arg1 == "-h" || arg1 == "--help") {
        command->type = HELP;
        command->arg = "";
        return command;
    }

    command->type = ERROR;
    command->arg = arg1;
    return command;
}

Command* CLI::parseCommand(std::string arg1, std::string arg2) {
    Command* command = new Command();

    if (arg1 == "-h" || arg1 == "--help") {
        command->type = HELP;
        command->arg = arg2;
    } else if (arg1 == "-o" || arg1 == "--out") {
        command->type = OUT;
        command->arg = arg2;
    } else if (arg1 == "-i" || arg1 == "--in") {
        command->type = IN;
        command->arg = arg2;
    } else if (arg1 == "-t" || arg1 == "--tree") {
        command->type = TREE;
        command->arg = arg2;
    } else if (arg1 == "-m" || arg1 == "--mode") {
        command->type = MODE;
        command->arg = arg2;
    } else {
        command->type = ERROR;
        command->arg = arg1 + " "+ arg2;
    }

    return command;
}

//TODO: check for flag without arg e.g. -o
std::vector<Command>* CLI::parse() {
    auto* args = new std::vector<Command>();

    if (argc < 2) {
        Command command = {HELP, ""};
        args->push_back(command);
        return args;
    }

    for (int i = 1; i < argc; i++) {
        Command* command = parseCommand(argv[i]);
        if (command->type == HELP) {
            args->clear();
            args->push_back(*command);
            break;
        } else if (command->type == ERROR && i+1 < argc) {
            command = parseCommand(argv[i], argv[i+1]);
            i++;
        }
        if (command->type == ERROR) {
            args->clear();
            args->push_back(*command);
            break;
        }
        args->push_back(*command);
    }

    return args;
}