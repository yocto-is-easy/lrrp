#include "request.h"

// define all the functions in request.h
lrrp::request::request() {
    body = json::object();
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
