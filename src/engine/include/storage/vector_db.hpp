#pragma once
#include <string>
#include "db_config.hpp"
#include "storage_manager.hpp"
#include "collection_manager.hpp"

namespace vectordb{

class VectorDB{
public:
    VectorDB(const string& storagePath);

    bool init();

    bool load();

    CollectionManager& collections(){return *_collectionManager;}

private:
   std::string _storagePath;
   DBConfig _dbConfig;

   std::unique_ptr<StorageManager> _storage;
   std::unique_ptr<CollectionManager> _collectionManager;

   bool loadBBConfig();
   bool saveDBConfig();
}

}

// #pragma once
// #include <string>
// #include <vector>
// #include "db_config.hpp"
// #include "collection_manager.hpp"

// namespace VectorStorage {

// class VectorStorage{
// private:
//     std::string _storagePath;
//     DBConfig _dbConfig;
//     CollectionManager _collectionManager;

//     bool loadDBConfig();
//     bool saveDBConfig();

// public:
//     VectorStorage(const std::string& storagePath);

//     bool init();
//     bool load();

//     CollectionManager& collections() { return _collectionManager; }
// };

// }


// #pragma once
// #include <string>

// class Storage{
// private:
//     std::string root;
//     std::string snapshot;

// public:
//     explicit Storage(const std::string& rootpath, const std::string& snapshotpath);
//     void init();

//     const std::string& getRootPath() const { return root; }
//     const std::string& getSnapshotPath() const { return snapshot; }
// };