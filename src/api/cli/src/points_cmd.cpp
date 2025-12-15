#include "../cli.h"
#include "../include/utils.h"
#include <iostream>

namespace zoro::cli{

void Cli::PointsHelp(){
    std::cout << "\nCommands:\n\n";

    PrintCmd("points upsert <collection_name>","Insert or update points",40);
    PrintCmd("points delete <collection_name>", "Delete points", 40);
    PrintCmd("points count <collection_name>", "Count points in a collection", 40);
    PrintCmd("points search <collection_name>", "Search points by similarity", 40);
}

void Cli::CmdPointsUpsert(const std::vector<std::string>& tokens){
    //TOD: Upsert Points
}

void Cli::CmdPointsDelete(const std::vector<std::string>& tokens){
    //TODO: Delete Points
}

void Cli::CmdPointsCount(const std::vector<std::string>& tokens){
    //TODO: Count Points
}

void Cli::CmdPointsSearch(const std::vector<std::string>& tokens){
    //TODO: Search Points
}

void Cli::CmdPoints(const std::vector<std::string>& tokens) {

    std::string action = tokens[1];
    
    if(action=="upsert") CmdPointsUpsert(tokens);
    else if(action=="delete") CmdPointsDelete(tokens);
    else if(action=="count") CmdPointsCount(tokens);
    else if(action=="search") CmdPointsSearch(tokens);
    else if(action=="--help") PointsHelp();
    else ShowWarning(tokens[0]);

}

}