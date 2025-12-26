#pragma once
#include <string>
#include <vector>
#include "../../services/include/CollectionService.h"

namespace zoro::cli {

class Cli {
public:
    explicit Cli(zoro::services::CollectionService* service);
    void Run();

private:
    zoro::services::CollectionService* service_; 

    void HandleCommand(const std::string& input);
    void ShowWarning(std::string target);

    void CmdCollection(const std::vector<std::string>& tokens);
    void CmdCollectionCreate(const std::vector<std::string>& tokens);
    void CmdCollectionDelete(const std::vector<std::string>& tokens);
    void CmdCollectionList(const std::vector<std::string>& tokens);
    void CmdCollectionInfo(const std::vector<std::string>& tokens);
    void CollectionHelp();
    
    void CmdPoints(const std::vector<std::string>& tokens);
    void CmdPointsUpsert(const std::vector<std::string>& tokens);
    void CmdPointsDelete(const std::vector<std::string>& tokens);
    void CmdPointsCount(const std::vector<std::string>& tokens);
    void CmdPointsSearch(const std::vector<std::string>& tokens);
    void PointsHelp();
};

}
