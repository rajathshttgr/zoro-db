#pragma once

class CollectionManager {
public:
    CollectionManager(const std::string& storagePath);

    bool createCollection(const std::string& name);
    bool deleteCollection(const std::string& name);
    std::unique_ptr<Collection> openCollection(const std::string& name);

private:
    std::string _storagePath;
};
