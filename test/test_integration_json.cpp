#include "gtest/gtest.h"

#include <nlohmann/json.hpp>

using namespace nlohmann;

TEST(Json, test1) {
    json j = {{"one", 1}, {"two", 2}};
    ASSERT_EQ(j.dump(), "{\"one\":1,\"two\":2}");
}
