#pragma once

#include "request.h"
#include "response.h"

namespace lrrp
{
    class handler_base {
    public:
        virtual response handle(const request& req) = 0;
    };
}
