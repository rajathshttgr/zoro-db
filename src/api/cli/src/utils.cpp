#include "../include/utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unordered_set>


namespace zoro::cli {

void PrintCmd(const std::string& cmd, const std::string& desc, int width, bool isHeader) {
    
    if (isHeader) {
        int totalWidth = 0;
        totalWidth = width+desc.length()+2;
        std::cout << std::string(totalWidth, '-') << '\n';
    }

    std::cout << "  "
              << std::left << std::setw(width)
              << cmd
              << desc << '\n';

}

void PrintTableRow(const std::vector<std::string>& columns,
                   const std::vector<int>& widths,
                   bool isHeader)
{
    for (size_t i = 0; i < columns.size(); ++i) {
        std::cout << std::left << std::setw(widths[i]) << columns[i];
        if (i + 1 < columns.size()) std::cout << "  "; // column gap
    }
    std::cout << '\n';

    if (isHeader) {
        int total = 0;
        for (auto w : widths) total += w;
        total += (columns.size() - 1) * 2;
        std::cout << std::string(total, '-') << '\n';
    }
}


bool IsNumber(const std::string& s) {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(),
                       [](unsigned char c){ return std::isdigit(c); });
}

bool IsValidDistance(const std::string& s) {
    static const std::unordered_set<std::string> valid{
        "dot", "cosine", "euclid"
    };
    return valid.count(s) > 0;
}

}

