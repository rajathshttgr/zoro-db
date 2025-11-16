#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "config.hpp"
#include "storage/storage.hpp"
#include "storage/collection.hpp"
#include "core/version.hpp"

std::string VERSION = version_info();

std::vector<std::string> split(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) tokens.push_back(word);
    return tokens;
}

void handleCommand(const std::string& line, Storage& storage) {
    auto tokens = split(line);
    if (tokens.empty()) return;

    const std::string& cmd = tokens[0];

    if (cmd == "exit") {
        exit(0);
    } 
    else if (cmd == "version") {
        std::cout << VERSION << std::endl;
    } 
    else if (cmd == "set" && tokens.size() >= 3 && tokens[1] == "collection") {
        std::string name = tokens[2];
        Collection::Create(name, storage.getRootPath());
        std::cout << "Created collection " << name << "\n";
    } 
    else {
        std::cout << "Invalid Input!" << std::endl;
    }
}

int main() {
    std::cout << "Welcome to zoro-db " << VERSION << std::endl;

    Config cfg = Config::load("bin/config.yaml");
    Storage storage(cfg.storage.storage_path, cfg.storage.snapshot_path);
    storage.init();

    std::string line;
    while (true) {
        std::cout << "\nEnter Command: ";
        std::getline(std::cin, line);
        handleCommand(line, storage);
    }
}
