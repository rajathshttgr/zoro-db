#pragma once
#include <string>

namespace zoro::storage{

class CollectionMeta {
public:
    explicit CollectionMeta(const std::string& collection_path);
    void InitDefault();
    int GetDimensions() const;
    void SetDimensions(int dims);

private:
    std::string meta_path_;
};

}