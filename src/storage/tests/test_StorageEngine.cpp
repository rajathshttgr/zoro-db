// last updated 28 Dec 2025, tests: passing

#include <gtest/gtest.h>
#include "../include/StorageEngine.h"
#include "fake_wal.h"
#include <filesystem>

using namespace zoro::storage;

class StorageEngineTest : public ::testing::Test {
protected:
    std::string test_root = "test_data";
    FakeWAL wal;

    void SetUp() override {
        std::filesystem::remove_all(test_root);
    }

    void TearDown() override {
        std::filesystem::remove_all(test_root);
    }
};

TEST_F(StorageEngineTest,CreateCollection){
    StorageEngine engine(test_root, wal);

    ASSERT_TRUE(engine.CreateCollection("users", 100, "dot"));
    ASSERT_TRUE(engine.CollectionExists("users"));

    // WAL interaction verified
    ASSERT_EQ(wal.create_calls, 1);
}

TEST_F(StorageEngineTest, CreateCollectionTwiceFails){
    StorageEngine engine(test_root, wal);

    ASSERT_TRUE(engine.CreateCollection("users", 100, "dot"));

    ASSERT_FALSE(engine.CreateCollection("users", 100, "dot"));
}

TEST_F(StorageEngineTest, DeleteCollection){
    StorageEngine engine(test_root, wal);

    ASSERT_TRUE(engine.CreateCollection("users", 100, "dot"));
    ASSERT_TRUE(engine.CollectionExists("users"));

    ASSERT_TRUE(engine.DeleteCollection("users"));
    ASSERT_FALSE(engine.CollectionExists("users"));
}

TEST_F(StorageEngineTest, ListCollections){
    StorageEngine engine(test_root, wal);

    ASSERT_TRUE(engine.CreateCollection("users_a", 100, "dot"));
    ASSERT_TRUE(engine.CreateCollection("users_b", 100, "dot"));

    auto list =engine.ListCollections();
    ASSERT_EQ(list.size(),2);
}