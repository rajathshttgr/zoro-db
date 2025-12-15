#include "../include/utils.h"
#include "../../../config.h"
#include <iostream>
#include <iomanip>

std::string version = zoro::config::getVersion();

namespace zoro::cli {


void PrintGreetings() {

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
            std::cout << " " << version;
        }
        
        std::cout << std::endl;
    }

    std::cout << "ZoroDB —  a tiny Vector Search Engine\n\n";

    std::cout << "Get started:\n";
    std::cout << "  " << std::left << std::setw(15) << "zoro --help"<< "Show all commands\n";
    std::cout << "  " << std::left << std::setw(15) << "zoro init"<< "Initialize a new database\n\n";

    std::cout << "Docs & examples:\n";
    std::cout << "  https://github.com/rajathshttgr/zoro-db\n";
}

void GetVersion(){
    std::cout<<version<<std::endl;
}

}