#include <gtest/gtest.h>
#include "../include/StorageEngine.h"
#include "fake_wal.h"
#include <filesystem>

using namespace zoro::storage;

class PointsUpsertTest : public ::testing::Test {
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

TEST_F(PointsUpsertTest, UpsertCollectionPoints){
    StorageEngine engine(test_root, wal);

    ASSERT_TRUE(engine.CreateCollection("users", 100, "dot"));

    ASSERT_TRUE(engine.UpsertPoints("users"));
}