#include "request.h"

// define all the functions in request.h
lrrp::request::request() {
    body = json::object();
}

lrrp::request::request(const std::string& raw) {
    body = json::parse(raw);
}

void lrrp::request::set_route(const std::string& route) {
    body["route"] = route;
}

json lrrp::request::jsonify() {
    return body;
}

std::string lrrp::request::stringify() {
    return body.dump();
}

lrrp::request lrrp::request::from_string(const std::string& raw) {
    return request(raw);
}
