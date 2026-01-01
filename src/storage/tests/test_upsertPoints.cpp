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

    // void TearDown() override {
    //     std::filesystem::remove_all(test_root);
    // }
};

TEST_F(PointsUpsertTest, UpsertCollectionPoints){
    StorageEngine engine(test_root, wal);

    ASSERT_TRUE(engine.CreateCollection("users", 10, "dot"));

    std::vector<float> vectors = {
        0.2f, 0.3f, 0.34f, 0.23f, 0.67f,
        0.2f, 0.3f, 0.34f, 0.23f, 0.67f
    };

    zoro::storage::json payload = {
        {"key", "value1"},
        {"key2", "value2"}
    };

    ASSERT_TRUE(engine.UpsertPoints("users", 910, vectors, payload));
    ASSERT_TRUE(engine.UpsertPoints("users", 910, vectors, payload));
}