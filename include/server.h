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
        std::map<std::string, std::unique_ptr<handler_base>> handlers;
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

        void add_handler(const std::string& route, std::unique_ptr<handler_base> handler);
        void set_ip_version(ip_version ip_version);

        void run();
        void run_async();
        void stop();
    };
}
