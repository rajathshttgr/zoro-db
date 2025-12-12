#include <gtest/gtest.h>
#include "../include/Catalog.h"
#include <filesystem>

using namespace zoro::storage;

class CatalogTest:
public::testing::Test{
protected:
    std::string testRoot = "catalog_test";
    std::string collectionRoot=testRoot+"/collections";

    void SetUp() override{
        std::filesystem::remove_all(testRoot);
        std::filesystem::create_directories(testRoot);
    }

    void TearDown() override{
        std::filesystem::remove_all(testRoot);
    };

};

TEST_F(CatalogTest, AddAndListCollections){
    Catalog c(testRoot);

    ASSERT_TRUE(c.AddCollection("users",collectionRoot+"/users"));
    ASSERT_TRUE(c.AddCollection("orders",collectionRoot+"/orders"));

    auto list=c.ListCollections();

    ASSERT_EQ(list.size(),2);
    ASSERT_TRUE(std::find(list.begin(),list.end(),"users")!=list.end());
    ASSERT_TRUE(std::find(list.begin(),list.end(),"orders")!=list.end());
}


TEST_F(CatalogTest, RemoveCollection){
    Catalog c(testRoot);

    c.AddCollection("users",collectionRoot+"/users");
    ASSERT_TRUE(c.RemoveCollection("users"));

    ASSERT_FALSE(c.RemoveCollection("users"));

    auto list=c.ListCollections();
    ASSERT_TRUE(list.empty());
}