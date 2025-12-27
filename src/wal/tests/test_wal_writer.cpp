#include <gtest/gtest.h>
#include "../include/wal_writer.h"
#include <filesystem>

using namespace zoro::wal;

class WALWriterTest:public::testing::Test{
protected:
    std::string test_root="./storage/test_data";

    void SetUp() override{
        std::filesystem::remove_all(test_root);
        std::filesystem::create_directories(test_root);
    }

    void TearDown() override{
        std::filesystem::remove_all(test_root);
    }
};

TEST_F(WALWriterTest, AppendCreateCollection) {
    WALWriter wal(test_root);
    ASSERT_TRUE(wal.append_create_collection("b", 64, DistType::COSINE));
}

TEST_F(WALWriterTest, AppendDeleteCollection){
    WALWriter wal(test_root);
    ASSERT_TRUE(wal.append_delete_collection(100));
}
