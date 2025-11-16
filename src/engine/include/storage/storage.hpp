#pragma once
#include <string>

class Storage{
private:
    std::string root;
    std::string snapshot;

public:
    explicit Storage(const std::string& rootpath, const std::string& snapshotpath);
    void init();

    const std::string& getRootPath() const { return root; }
    const std::string& getSnapshotPath() const { return snapshot; }
};