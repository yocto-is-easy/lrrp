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

lrrp::client::client(const std::string& host, int port)
    : host_(host), port_(port) {
}

lrrp::response lrrp::client::send(request& req) {
    asio::ip::tcp::socket socket(context_);

    try{
        socket.connect(
            asio::ip::tcp::endpoint(
                asio::ip::address::from_string(host_),
                port_));

        asio::write(socket, asio::buffer(req.stringify() + end_msg));

        std::string response_str;
        asio::read_until(socket, asio::dynamic_buffer(response_str), end_msg);
        socket.close();
        return response::from_string(response_str);
    } catch(const std::exception& e) {
        return lrrp::response_builder().set_status(lrrp::internal_error).build();
    }
}

}
