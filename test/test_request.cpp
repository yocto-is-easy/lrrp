#include "gtest/gtest.h"

#include "request.h"

using namespace lrrp;

TEST(request, init)
{
    request req;
    EXPECT_EQ(req.jsonify().empty(), true);
}

TEST(request, build_request1)
{
    request req = request_builder("the_route")
            .set_param("key", "value")
            .build();

    EXPECT_EQ(req.jsonify()["route"], "the_route");
    EXPECT_EQ(req.jsonify()["params"]["key"], "value");
}
