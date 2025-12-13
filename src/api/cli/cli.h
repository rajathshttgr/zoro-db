#pragma once

#include <string>
#include "../CollectionService.h"

namespace zoro::cli {

class Cli {
public:
    explicit Cli(zoro::api::CollectionService* service);
    void Run();

private:
    zoro::api::CollectionService* service_;

    void HandleCommand(const std::string& input);
    void CmdCreate(const std::vector<std::string>& tokens);
    void CmdDelete(const std::vector<std::string>& tokens);
    void CmdList();
};

}