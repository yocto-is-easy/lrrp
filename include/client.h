#pragma once

#include "response.h"
#include "request.h"
#include "server.h"

#include <boost/asio.hpp>

using namespace boost;

namespace lrrp
{
    class client {
        std::string host_;
        int port_;
        asio::io_context context_;
    public:
        client(const std::string& host, int port);

        response send(request& req);
    };
}
