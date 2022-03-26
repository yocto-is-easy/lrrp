#include "request.h"

lrrp::request_builder::request_builder(const std::string& route) : req_() {
    req_.set_route(route);
}

lrrp::request lrrp::request_builder::build() {
    return req_;
}
