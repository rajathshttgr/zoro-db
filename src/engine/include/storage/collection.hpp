#pragma once
#include <string>
#include <cstdint>

class Collection {
public:
    Collection(const std::string& rootPath,
               const std::string& name);

    bool create();
    bool load();

    bool addPoint(const Point& p);
    std::optional<Point> getPoint(uint64_t id);
    bool updatePoint(const Point& p);
    bool deletePoint(uint64_t id);

    CollectionConfig config;
private:
    std::string _rootPath;
    std::string _name;
    std::vector<std::unique_ptr<Segment>> _segments;

    void loadSegments();
    uint32_t getSegmentIndexForID(uint64_t id) const;
    bool createNewSegment();
};



// #pragma once
// #include <string>

// class Collection{
// private:
//     std::string storageRoot;
// public:
//     explicit Collection(const std::string& storageRoot);

//     std::string Create(const std::string& collection_id);

//     std::string GetInfo(const std::string& collection_id); 
// };