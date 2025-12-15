#include "../include/utils.h"
#include <iostream>

namespace zoro::cli {

void PrintHelp(){
    std::cout << "\nCommands:\n";

    PrintCmd("collection create", "Create a new collection");
    PrintCmd("collection delete", "Delete a collection");
    PrintCmd("collection list",   "List all collections");
    PrintCmd("collection info",   "Show collection details");

    std::cout << '\n';

    PrintCmd("points upsert", "Insert or update points");
    PrintCmd("points delete", "Delete points");
    PrintCmd("points count",  "Count points in a collection");
    PrintCmd("points search", "Search points by similarity");

    std::cout << '\n';

    PrintCmd("ping",   "Check if server is alive");
    PrintCmd("health", "Run system diagnostics");

    std::cout << '\n';

    PrintCmd("--version", "Show version");
    PrintCmd("--help",    "Show help");
    PrintCmd("exit",      "Exit the app");

    std::cout << std::endl;
}


}