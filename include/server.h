#pragma once

#include <map>
#include <memory>

#include "request.h"
#include "response.h"
#include "handler_base.h"
#include "thread_pool.h"

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
        std::map<std::string, std::function<lrrp::response(const lrrp::request&)>> handlers;

        asio::io_context context_;
        std::unique_ptr<asio::ip::tcp::acceptor> acceptor_;
        bool should_stop = false;
        std::unique_ptr<lrrp::thread_pool<asio::ip::tcp::socket>> pool;
        std::mutex task_mutex;
        std::function<void(boost::asio::ip::tcp::socket &&)> default_worker;
        int port_;

        void proceed(asio::ip::tcp::socket&& sock);
    public:
        server(int port, int num_of_workers = std::thread::hardware_concurrency(), ip_version ip_version = ipv4);

        int add_handler(const std::string& route, std::function<lrrp::response(const lrrp::request&)> handler);
        void set_ip_version(ip_version ip_version);

        void run();
        void run_async();
        void stop();
    };

lrrp::server::server(int port, int num_of_workers, ip_version ip_version) : port_(port) {
    default_worker = std::bind(&server::proceed, this, std::placeholders::_1);

    pool = std::make_unique<thread_pool<asio::ip::tcp::socket>>(num_of_workers);
    pool->set_worker(default_worker);

    set_ip_version(ip_version);
}

void lrrp::server::set_ip_version(ip_version ip_version) {
    asio::ip::tcp::endpoint endpoint;
    if (ip_version == ipv4) {
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port_);
    } else if(ip_version == ipv6) {
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v6(), port_);
    }

    acceptor_ = std::make_unique<asio::ip::tcp::acceptor>(context_, endpoint);
}

int lrrp::server::add_handler(const std::string& route, std::function<lrrp::response(const lrrp::request&)> handler) {
    handlers[route] = handler;
    return handlers.size() - 1;
}

void lrrp::server::run_async() {
    while (!should_stop) {
        if(!pool->is_full()) {
            asio::ip::tcp::socket socket(context_);
            acceptor_->accept(socket);

            task_mutex.lock();
            pool->enqueue(std::move(socket));
            task_mutex.unlock();
        }
    }
}

void lrrp::server::run() {
    while(!should_stop) {
        asio::ip::tcp::socket socket(context_);
        acceptor_->accept(socket);

        proceed(std::move(socket));
    }
}

void lrrp::server::stop() {
    should_stop = true;
    pool->stop();
}

void lrrp::server::proceed(asio::ip::tcp::socket&& socket) {
    std::string request_str;
    asio::read_until(socket, asio::dynamic_buffer(request_str), end_msg);

    request req = request::from_string(request_str);

    response res = handlers[req.jsonify()["route"]](req);
    asio::write(socket, asio::buffer(res.stringify() + end_msg));

    socket.close();
}

}
