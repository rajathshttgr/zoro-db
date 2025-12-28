// last updated 28 Dec 2025, tests: passing

#include <gtest/gtest.h>
#include "../include/CollectionMeta.h"
#include "../include/FileUtils.h"
#include <filesystem>

using namespace zoro::storage;

class CollectionMetaTest:
public::testing::Test{
protected:
    std::string collection_path = "meta_test/collection";

    void SetUp() override{
        std::filesystem::remove_all("meta_test");
        std::filesystem::create_directories(collection_path);
    };

    void TearDown() override{
        std::filesystem::remove_all("meta_test");
    };

};

TEST_F(CollectionMetaTest, InitDefaultCreatesMetaFile){
    CollectionMeta meta(collection_path);

    meta.InitDefault(1536,"DOT", 101, "users"); 

    ASSERT_TRUE(FileUtils::Exists(collection_path+"/meta.json"));
}

TEST_F(CollectionMetaTest, SetAndGetDimensions) {
    CollectionMeta meta(collection_path);

    meta.InitDefault(1536,"DOT", 101, "users"); 
    meta.SetDimensions(1536);


    ASSERT_EQ(meta.GetDimensions(), 1536);
}

TEST_F(CollectionMetaTest, SetAndGetDistance){
    CollectionMeta meta(collection_path);

    meta.InitDefault(1536,"DOT", 101, "users"); 

    ASSERT_EQ(meta.GetDistance(), "DOT");
}

TEST_F(CollectionMetaTest, SetAndGetCollectionId){
    CollectionMeta meta(collection_path);

    meta.InitDefault(1536,"DOT", 101, "users"); 

    ASSERT_EQ(meta.GetCollectionId(), 101);
}

