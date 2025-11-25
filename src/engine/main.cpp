#include <iostream>
#include <string>
#include "include/version.hpp"
#include "storage/vector_db.hpp"
#include "storage/collection.hpp"
#include "storage/point.hpp"

void printHelp() {
    std::string version = version_info();
    std::cout << "zoro "<<version<<" CLI Commands:\n"
              << "  > init\n"
              << "  > list-collections\n"
              << "  > create-collection <name>\n"
              << "  > delete-collection <name>\n"
              << "  > add-point <collection> <id> <value>\n"
              << "  > get-point <collection> <id>\n"
              << "  > update-point <collection> <id> <value>\n"
              << "  > delete-point <collection> <id>\n"
              << "  > help\n";
}

int main(int argc, char** argv) {
    std::string storagePath = "../../.storage";

    if(argc<2){
        printHelp();
        return 0;
    }

    std::string command = argv[1];

    VectorStorage db(storagePath);

    if (command == "help") {
        printHelp();
        return 0;
    }

    if (command == "init") {
        if(db.init()){
            std::cout << "Database initialized at " << storagePath << "\n";
        }else{
            std::cout << "Failed to initialize database.\n";
        }
        return 0;
    }

    if(db.load()){
        std::cout << "Failed to load DB. Have you run 'init'?\n";
        return 1;
    }

    if(command=="list-collections"){
        auto& mgr = db.collections();
        auto names = mgr.listCollections();

        for(auto& n:names){
            std::cout<<n<<"\n";
        }
        return 0;
    }

    std::cout << "Unknown command: " << command << "\n";
    printHelp();

    return 1;
}





// #include <iostream>
// #include <string>
// #include <vector>
// #include <sstream>
// #include "config.hpp"
// #include "storage/storage.hpp"
// #include "storage/collection.hpp"
// #include "core/version.hpp"

// std::string VERSION = version_info();

// std::vector<std::string> split(const std::string& line) {
//     std::vector<std::string> tokens;
//     std::istringstream iss(line);
//     std::string word;
//     while (iss >> word) tokens.push_back(word);
//     return tokens;
// }

// void handleCommand(const std::string& line, Storage& storage, Collection& collection) {
//     auto tokens = split(line);
//     if (tokens.empty()) return;

//     const std::string& cmd = tokens[0];

//     if (cmd == "exit") {
//         exit(0);
//     } 
//     else if (cmd == "version") {
//         std::cout << VERSION << std::endl;
//     } 
//     else if (cmd == "set" && tokens.size() >= 3 && tokens[1] == "collection") {
//         std::string collection_id = tokens[2];
//         std::cout << collection.Create(collection_id) << std::endl;
//     }
//     else if (cmd == "get" && tokens.size() >= 3 && tokens[1] == "collection") {
//         std::string collection_id = tokens[2];
//         std::cout << collection.GetInfo(collection_id) << std::endl;
//     }
//     else {
//         std::cout << "Invalid Input!" << std::endl;
//     }
// }


// int main() {
//     std::cout << "Welcome to zoro-db " << VERSION << std::endl;

//     Config cfg = Config::load("bin/config.yaml");
//     Storage storage(cfg.storage.storage_path, cfg.storage.snapshot_path);
//     Collection collection(cfg.storage.storage_path);
//     storage.init();

//     std::string line;
//     while (true) {
//         std::cout << "\nEnter Command: ";
//         std::getline(std::cin, line);
//         handleCommand(line, storage, collection);
//     }
// }
