#include <gtest/gtest.h>
#include "version.hpp"

TEST(VersionTest, NonEmptyString) {
    std::string v = version_info();
    EXPECT_FALSE(v.empty());
}

// TEST(VersionTest, StartsWithV) {
//     EXPECT_TRUE(version_info().starts_with("v"));
// }