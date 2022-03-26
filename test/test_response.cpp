#include "gtest/gtest.h"

#include "response.h"

using namespace lrrp;

TEST(response, init)
{
    response res = response_builder().set_payload({{"key", "value"}}).build();
    EXPECT_EQ(res.jsonify()["payload"], json::object({{"key", "value"}}));
}

TEST(response, build_response1)
{
    response res = response_builder()
            .set_payload({{"key", "value"}})
            .set_status(status_type::ok)
            .build();

    EXPECT_EQ(res.jsonify()["payload"], json::object({{"key", "value"}}));
    EXPECT_EQ(res.jsonify()["status"], status_type::ok);
}

TEST(response, serialize_deserialize)
{
    response res = response_builder()
            .set_payload({{"key", "value"}})
            .set_status(status_type::ok)
            .build();

    std::string raw = res.stringify();
    response res2 = response::from_string(raw);

    EXPECT_EQ(res.jsonify()["payload"], res2.jsonify()["payload"]);
    EXPECT_EQ(res.jsonify()["status"], res2.jsonify()["status"]);
}

TEST(response, stringify)
{
    response res = response_builder()
            .set_payload({{"key", "value"}})
            .set_status(status_type::ok)
            .build();

    std::string raw = res.stringify();
    EXPECT_EQ(raw, "{\"payload\":{\"key\":\"value\"},\"status\":0}");
}
