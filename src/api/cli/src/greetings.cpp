#include "../include/utils.h"
#include "../../../config.h"
#include <iostream>
#include <iomanip>

std::string version = zoro::config::getVersion();

namespace zoro::cli {


void PrintGreetings() {
    const std::string BOLD  = "\033[1m";
    const std::string RESET = "\033[0m";

    const char* title[] = {
        "███████╗ ██████╗ ██████╗  ██████╗",
        "╚══███╔╝██╔═══██╗██╔══██╗██╔═══██╗",
        "  ███╔╝ ██║   ██║██████╔╝██║   ██║",
        " ███╔╝  ██║   ██║██╔══██╗██║   ██║",
        "███████╗╚██████╔╝██║  ██║╚██████╔╝",
        "╚══════╝ ╚═════╝ ╚═╝  ╚═╝ ╚═════╝",
    };

    std::cout << "\n";
    for (auto line : title) {
        std::cout << BOLD << line << RESET << "\n";
    }

    std::cout << "\nZoroDB — a tiny vector search engine\n";
    std::cout << "Type 'help' for commands, 'exit' to quit\n\n";
}


void GetVersion(){
    std::cout<<version<<std::endl;
}

}