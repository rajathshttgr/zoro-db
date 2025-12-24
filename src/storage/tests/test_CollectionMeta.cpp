#include <gtest/gtest.h>
#include "../include/CollectionMeta.h"
#include "../include/FileUtils.h"
#include <filesystem>

using namespace zoro::storage;

class CollectionMetaTest:
public::testing::Test{
protected:
    std::string path = "meta_test/collection";

    void SetUp() override{
        std::filesystem::remove_all("meta_test");
        std::filesystem::create_directories(path);
    };

    void TearDown() override{
        std::filesystem::remove_all("meta_test");
    };

};

TEST_F(CollectionMetaTest, InitDefaultCreatesMetaFile){
    CollectionMeta meta(path);

    meta.InitDefault(); //tests need to be updated immidately

    ASSERT_TRUE(FileUtils::Exists(path+"/meta.json"));
}


TEST_F(CollectionMetaTest, SetAndGetDimensions) {
    CollectionMeta meta(path);

    meta.InitDefault();
    meta.SetDimensions(1567);

    ASSERT_EQ(meta.GetDimensions(), 1567);
}