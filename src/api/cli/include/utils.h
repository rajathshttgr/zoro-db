#pragma once
#include <string>
#include <vector>

namespace zoro::cli {
    void PrintGreetings();
    void PrintHelp();
    void Ping();
    void Health();
    void GetVersion();
    void PrintCmd(const std::string& cmd, const std::string& desc, int width=22,bool isHeader=false);
    void PrintTableRow(const std::vector<std::string>& columns, const std::vector<int>& widths, bool isHeader = false);
    bool IsNumber(const std::string& s);
    bool IsValidDistance(const std::string& s);
}