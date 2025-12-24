#include "../cli.h"
#include "../include/utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <iomanip>

namespace zoro::cli{


void Cli::CollectionHelp(){
    std::cout << "\nCommands:\n\n";


    PrintCmd("collection create <collection_name>","create a new collection",40);
    std::cout<<"    --dimension <int>\n";
    std::cout<<"    --distance <dot|cosine|euclidean>\n";
    PrintCmd("collection delete <collection_name>", "Delete a collection", 40);
    PrintCmd("collection list", "List all the collections", 40);
    PrintCmd("collection info <collection_name>", "Show collection details", 40);
}


void Cli::ShowWarning(std::string target){
    std::cout<<"Invalid Command! try "<<target<<" --help"<<std::endl;
};


void Cli::CmdCollectionCreate(const std::vector<std::string>& tokens) {

    if (tokens.size() < 3) {
        ShowWarning(tokens[0]);
        return;
    }

    std::string collection_name = tokens[2];
    int dimension = -1;
    std::string distance;
    std::string err;

    for (size_t i = 2; i + 1 < tokens.size(); ++i) {

        if (tokens[i] == "--dimension") {
            std::string value = tokens[++i];
            if (IsNumber(value)) {
                dimension = std::stoi(value);
            } else {
                std::cout << "Invalid value for --dimension: " << value << "\n";
            }
        }
        else if (tokens[i] == "--distance") {
            std::string value = tokens[++i];
            if (IsValidDistance(value)) {
                distance = value;
            } else {
                std::cout << "Invalid value for --distance: " << value << "\n";
            }
        }
    }

    while (dimension < 1 || dimension > 9999) {
        std::cout << "--dimension (1–9999): ";

        std::string line;
        std::getline(std::cin, line);

        if (!IsNumber(line)) {
            std::cout << "Invalid dimension. Please enter a number.\n";
            continue;
        }

        int value = std::stoi(line);

        if (value < 1 || value > 9999) {
            std::cout << "Dimension out of range.\n";
            continue;
        }

        dimension = value;
    }


    while (!IsValidDistance(distance)) {
        std::cout << "--distance (dot | cosine | euclid): ";
        std::getline(std::cin, distance);
    }

    if (!service_->CreateCollection(collection_name, dimension, distance, err)) {
        std::cout << "Error: " << err << "\n";
        return;
    }

    std::cout << "Collection '"<<collection_name<<"' created successfully.\n";
}


void Cli::CmdCollectionDelete(const std::vector<std::string>& tokens){

    if (tokens.size() < 3) {
        ShowWarning(tokens[0]);
        return;
    }

    std::string collection_name = tokens[2];
    std::string err;

    if (!service_->DeleteCollection(collection_name, err)) {
        std::cout << "Error: " << err << "\n";
        return;
    }

    std::cout << "Collection deleted.\n";
}


void Cli::CmdCollectionList(const std::vector<std::string>& tokens){
    std::vector<zoro::storage::CollectionInfo> collection_list = service_->ListCollections();

    if(collection_list.empty()){
        std::cout << "No collections found in DB" << std::endl;
        return;
    }

    std::vector<int> widths = {30, 10, 10}; 

    std::cout<<"\n";
    PrintTableRow({"Collection Name", "Distance", "Dimension"}, widths, true);

    for (const auto& collection : collection_list) {
        //TODO: show all meta data atleast in REST API
        PrintTableRow({collection.coll_name, collection.distance, std::to_string(collection.dimension)}, widths);
    }
}


void Cli::CmdCollectionInfo(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 3) {
        ShowWarning(tokens[0]);
        return;
    }

    std::string collection_name = tokens[2];
    std::string err;

    auto info_opt = service_->LoadCollection(collection_name, err);

    if (!info_opt.has_value()) {
        //show error
        return;
    }

    const auto& info = *info_opt;   // unwrap once
    
    std::cout << "\n";
    PrintCmd("coll_id", std::to_string(info.id));
    PrintCmd("coll_name", info.coll_name);
    PrintCmd("dimension", std::to_string(info.dimension));
    PrintCmd("distance", info.distance);
    PrintCmd("created_at", info.created_at);
    PrintCmd("status", info.status);

}


void Cli::CmdCollection(const std::vector<std::string>& tokens) {

    std::string action = tokens[1];
    
    if(action=="create") CmdCollectionCreate(tokens);
    else if(action=="delete") CmdCollectionDelete(tokens);
    else if(action=="list") CmdCollectionList(tokens);
    else if(action=="info") CmdCollectionInfo(tokens);
    else if(action=="--help") CollectionHelp();
    else ShowWarning(tokens[0]);
}

}