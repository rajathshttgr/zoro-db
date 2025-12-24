#include <gtest/gtest.h>
#include "../include/StorageEngine.h"
#include <filesystem>

using namespace zoro::storage;

class StorageEngineTest:
public::testing::Test{
protected:
    std::string testRoot="test_data";
    void SetUp() override{
        std::filesystem::remove_all(testRoot);
    }

    void TearDown() override{
        std::filesystem::remove_all(testRoot);
    }
};

TEST_F(StorageEngineTest,CreateCollection){
    StorageEngine engine(testRoot);

    ASSERT_TRUE(engine.CreateCollection("users",100));

    ASSERT_TRUE(engine.CollectionExists("users"));
}

TEST_F(StorageEngineTest, CreateCollectionTwiceFails){
    StorageEngine engine(testRoot);

    engine.CreateCollection("users",100);

    ASSERT_FALSE(engine.CreateCollection("users",100));
}

TEST_F(StorageEngineTest, DeleteCollection){
    StorageEngine engine(testRoot);

    engine.CreateCollection("users",100);
    ASSERT_TRUE(engine.CollectionExists("users"));

    ASSERT_TRUE(engine.DeleteCollection("users"));
    ASSERT_FALSE(engine.CollectionExists("users"));
}

TEST_F(StorageEngineTest, ListCollections){
    StorageEngine engine(testRoot);

    engine.CreateCollection("a",100);
    engine.CreateCollection("b",100);

    auto list =engine.ListCollections();
    ASSERT_EQ(list.size(),2);
}