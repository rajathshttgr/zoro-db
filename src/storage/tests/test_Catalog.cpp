// last updated 28 Dec 2025, tests: passing

#include <gtest/gtest.h>
#include "../include/Catalog.h"
#include <filesystem>

using namespace zoro::storage;

class CatalogTest:
public::testing::Test{
protected:
    std::string test_root = "catalog_test";
    std::string collectionRoot=test_root+"/collections";

    void SetUp() override{
        std::filesystem::remove_all(test_root);
        std::filesystem::create_directories(test_root);
    }

    void TearDown() override{
        std::filesystem::remove_all(test_root);
    };

};


TEST_F(CatalogTest, AddCollections){
    Catalog c(test_root);

    // test data
    std::string dist="dot";
    int dim=1536;
    int coll_id;

    ASSERT_TRUE(c.AddCollection("users", coll_id, dim, dist));
    EXPECT_EQ(100, coll_id);

    // test coll_id increment
    ASSERT_TRUE(c.AddCollection("products", coll_id, dim, dist));
    EXPECT_EQ(101, coll_id);

    // test duplicate collections
    EXPECT_FALSE(c.AddCollection("users", coll_id, dim, dist));

    // test invalid collection name, dimension, or distance
    EXPECT_FALSE(c.AddCollection("", coll_id, dim, dist));

    // invalid dimension
    dim=0;
    EXPECT_FALSE(c.AddCollection("", coll_id, dim, dist));

}

TEST_F(CatalogTest, ListCollection){
    Catalog c(test_root);

    // test data
    std::string dist="dot";
    int dim=1536;
    int coll_id;

    ASSERT_TRUE(c.AddCollection("users", coll_id, dim, dist));
    ASSERT_TRUE(c.AddCollection("products", coll_id, dim, dist));
    
    // test list collections in catalog
    auto list=c.ListCollections();
    ASSERT_EQ(list.size(),2);

    // test correct collection exists
    std::vector<std::string> collection_list;
    for(auto item:list){
        collection_list.push_back(item.coll_name);
    }
    ASSERT_TRUE(std::find(collection_list.begin(),collection_list.end(),"users")!=collection_list.end());
    ASSERT_TRUE(std::find(collection_list.begin(),collection_list.end(),"products")!=collection_list.end());

    // check false entry
    ASSERT_FALSE(std::find(collection_list.begin(),collection_list.end(),"false_collection")!=collection_list.end());
}


TEST_F(CatalogTest, RemoveCollection){
    Catalog c(test_root);

    // test data
    std::string dist="dot";
    int dim=1536;
    int coll_id;

    ASSERT_TRUE(c.AddCollection("users", coll_id, dim, dist));

    ASSERT_TRUE(c.RemoveCollection("users"));

    ASSERT_FALSE(c.RemoveCollection("users"));

    auto list=c.ListCollections();
    ASSERT_TRUE(list.empty());
}

TEST_F(CatalogTest, GetCollectionInfo) {
    Catalog c(test_root);

    std::string dist = "dot";
    int dim = 1536;
    int id;

    ASSERT_TRUE(c.AddCollection("users", id, dim, dist));

    auto info = c.GetCollectionInfo("users");
    ASSERT_TRUE(info.has_value());

    EXPECT_EQ(info->coll_name, "users");
    EXPECT_EQ(info->id, 100);
    EXPECT_EQ(info->dimension, dim);
    EXPECT_EQ(info->distance, dist);
    EXPECT_EQ(info->status, "active");

    // test invalid request
    info = c.GetCollectionInfo("missing");
    EXPECT_FALSE(info.has_value());
}

TEST_F(CatalogTest, ListCollections){
    Catalog c(test_root);

    std::string dist = "dot";
    int dim = 1536;
    int id;
    
    ASSERT_TRUE(c.AddCollection("users", id, dim, dist));
    ASSERT_TRUE(c.AddCollection("orders", id, dim, dist));

    auto list = c.ListCollections();

    ASSERT_EQ(list.size(), 2);

    std::unordered_map<std::string, CollectionInfo> map;
    for (const auto& info : list) {
        map[info.coll_name] = info;
    }

    ASSERT_TRUE(map.count("users"));
    EXPECT_EQ(map["users"].dimension, dim);
    EXPECT_EQ(map["users"].distance, dist);
    EXPECT_EQ(map["users"].status, "active");
    EXPECT_EQ(map["users"].id, 100);

    ASSERT_TRUE(map.count("orders"));
    EXPECT_EQ(map["orders"].dimension, dim);
    EXPECT_EQ(map["orders"].distance, dist);
    EXPECT_EQ(map["orders"].status, "active");
    EXPECT_EQ(map["orders"].id, 101);
}