#include "server.h"

lrrp::server::server(int port, ip_version ip_version) {
    asio::ip::tcp::endpoint endpoint;
    if (ip_version == ipv4) {
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);
    } else if (ip_version == ipv6) {
        endpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v6(), port);
    }

    acceptor_ = std::make_unique<asio::ip::tcp::acceptor>(context_, endpoint);
}

void lrrp::server::add_handler(const std::string& route, std::unique_ptr<lrrp::handler_base> handler) {
    handlers[route] = std::move(handler);
}

void lrrp::server::run() {
    while (!should_stop) {
        asio::ip::tcp::socket socket(context_);
        acceptor_->accept(socket);

        std::string request_str;
        asio::read_until(socket, asio::dynamic_buffer(request_str), end_msg);

        request req = request::from_string(request_str);
        response res = handlers[req.jsonify()["route"]]->handle(req);

        asio::write(socket, asio::buffer(res.stringify() + end_msg));
    }
}

void lrrp::server::stop() {
    should_stop = true;
}
