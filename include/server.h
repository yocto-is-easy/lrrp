#pragma once

#include <map>
#include <memory>

#include "request.h"
#include "response.h"
#include "handler_base.h"

#include <boost/asio.hpp>

using namespace boost;

namespace lrrp
{
    enum ip_version
    {
        ipv4,
        ipv6
    };

    const std::string end_msg = "\r\n\r\n";

    class server {
        std::map<std::string, std::unique_ptr<handler_base>> handlers;
        asio::io_context context_;
        std::unique_ptr<asio::ip::tcp::acceptor> acceptor_;
        bool should_stop = false;
    public:
        server(int port, ip_version ip_version = ipv4);

        void add_handler(const std::string& route, std::unique_ptr<handler_base> handler);

        void run();
        void stop();

        void proceed(asio::ip::tcp::socket&& sock);
    };
}
