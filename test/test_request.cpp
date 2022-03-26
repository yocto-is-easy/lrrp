#include "gtest/gtest.h"

#include "request.h"

using namespace lrrp;

TEST(request, init)
{
    request req = request_builder("").build();
    EXPECT_EQ(req.jsonify()["route"], "");
}

TEST(request, build_request1)
{
    request req = request_builder("the_route")
            .set_param("key", "value")
            .build();

    EXPECT_EQ(req.jsonify()["route"], "the_route");
    EXPECT_EQ(req.jsonify()["params"]["key"], "value");
}

TEST(requese, serialize_deserialize)
{
    request req = request_builder("the_route")
            .set_param("key", "value")
            .build();

    std::string raw = req.stringify();
    request req2 = request::from_string(raw);

    EXPECT_EQ(req.jsonify()["route"], req2.jsonify()["route"]);
    EXPECT_EQ(req.jsonify()["params"]["key"],
              req2.jsonify()["params"]["key"]);
}
