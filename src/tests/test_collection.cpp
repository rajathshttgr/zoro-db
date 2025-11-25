// #include <gtest/gtest.h>
// #include <filesystem>
// #include <fstream>
// #include <nlohmann/json.hpp>
// #include "storage/collection.hpp"

// namespace fs = std::filesystem;

// class CollectionTest : public ::testing::Test{
// protected:
//     fs::path tmpDir;

//     void SetUp() override{
//         tmpDir = fs::temp_directory_path() / "zorodb_test_col";
//         fs::remove_all(tmpDir);
//         fs::create_directories(tmpDir);
//     }

//     void TearDown() override {
//             fs::remove_all(tmpDir);
//     }
// };


// TEST_F(CollectionTest, CreatesNewCollection) {
//     std::string name = "users";
//     std::string id = Collection::Create(name, tmpDir.string());

//     fs::path colPath = tmpDir / id;

//     EXPECT_TRUE(fs::exists(colPath));
//     EXPECT_TRUE(fs::exists(colPath/"config.json"));
//     EXPECT_TRUE(fs::exists(colPath/"vectors.bin"));
//     EXPECT_TRUE(fs::exists(colPath/"payload.bin"));
//     EXPECT_TRUE(fs::exists(colPath/"wal"));

//     // Verify config.json content
//     std::ifstream file(colPath / "config.json");
//     nlohmann::json j;
//     file >> j;

//     EXPECT_EQ(j["name"], id);
//     EXPECT_EQ(j["dimension"], 128);
// }


// TEST_F(CollectionTest, CreatesIncrementedNames) {
//     std::string id1 = Collection::Create("data", tmpDir.string());
//     std::string id2 = Collection::Create("data", tmpDir.string());
//     std::string id3 = Collection::Create("data", tmpDir.string());

//     EXPECT_EQ(id1, "data");
//     EXPECT_EQ(id2, "data_1");
//     EXPECT_EQ(id3, "data_2");

//     EXPECT_TRUE(fs::exists(tmpDir / id1));
//     EXPECT_TRUE(fs::exists(tmpDir / id2));
//     EXPECT_TRUE(fs::exists(tmpDir / id3));
// }