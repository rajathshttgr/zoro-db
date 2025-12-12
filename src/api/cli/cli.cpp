#include "cli.h"
#include <iostream>
#include <sstream>

const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";


namespace zoro::cli {

std::string version = "0.0.1";

void printTitle() {
    const char* title[] = {
        " ____  ___  _ __ ___ ",
        "|_  / / _ \\| '__/ _ \\",
        " / / | (_) | | | (_) |",
        "/___| \\___/|_|  \\___/ ", 
        "                     ",
    };
    
    int lines = sizeof(title) / sizeof(title[0]);

    for (int i = 0; i < lines; ++i) {
        std::cout << title[i];
        
        if (i == 3) {
            std::cout << " v" << version;
        }
        
        std::cout << std::endl;
    }
}


Cli::Cli(zoro::api::CollectionService* service)
    : service_(service) {}

void Cli::Run() {
    std::string input;
    printTitle();
    std::cout << "Zoro-DB CLI\n";

    while (true) {
        std::cout << "\n" << GREEN << "zoro>" << RESET << " ";
        if (!std::getline(std::cin, input)) break;

        if (input == "exit") break;
        HandleCommand(input);
    }
}

void Cli::HandleCommand(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) tokens.push_back(token);
    if (tokens.empty()) return;

    std::string cmd = tokens[0];

    if (cmd == "create")      CmdCreate(tokens);
    else if (cmd == "delete") CmdDelete(tokens);
    else if (cmd == "list")   CmdList();
    else std::cout << "Unknown command: " << cmd << "\n";
}

void Cli::CmdCreate(const std::vector<std::string>& tokens) {
    if (tokens.size() != 3) {
        std::cout << "Usage: create <name> <dimension>\n";
        return;
    }

    std::string name = tokens[1];
    int dim = std::stoi(tokens[2]);

    std::string err;
    if (!service_->CreateCollection(name, dim, err)) {
        std::cout << "Error: " << err << "\n";
        return;
    }

    std::cout << "Collection '" << name << "' created.\n";
}

void Cli::CmdDelete(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        std::cout << "Usage: delete <name>\n";
        return;
    }

    std::string err;
    if (!service_->DeleteCollection(tokens[1], err)) {
        std::cout << "Error: " << err << "\n";
        return;
    }

    std::cout << "Collection deleted.\n";
}

void Cli::CmdList() {
    auto list = service_->ListCollections();
    if (list.empty()) {
        std::cout << "(no collections)\n";
        return;
    }
    for (auto& n : list) std::cout << n << "\n";
}

}

