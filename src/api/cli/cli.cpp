#include "cli.h"
#include "include/utils.h"
#include <iostream>
#include <sstream>

const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";
const std::string BOLD  = "\033[1m";

namespace zoro::cli {

Cli::Cli(zoro::services::CollectionService* service)
    : service_(service) {}

void Cli::Run() {
    std::string input;
    PrintGreetings();

    while (true) {
        std::cout << BOLD << GREEN << "zoro" << RESET << "> ";
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

    if(cmd=="help" || cmd=="--help") PrintHelp();
    else if(cmd=="version" || cmd=="--version") GetVersion();
    else if(cmd=="ping" || cmd=="PING") Ping();
    else if(cmd=="health") Health();
    else if (cmd == "collection") CmdCollection(tokens);
    else if (cmd == "points") CmdPoints(tokens);
    else std::cout << "Unknown command: " << cmd << "\n";
}

}

