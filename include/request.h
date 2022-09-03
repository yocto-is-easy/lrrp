#pragma once
#include <string>
#include <map>

#include <nlohmann/json.hpp>

using namespace nlohmann;

namespace lrrp
{
    class request {
        json body;

        friend class request_builder;

        request();
        request(const std::string& raw);

        void set_route(const std::string& route);

        // here can be set any base type or json object
        template <typename T>
        void set_param(const std::string& key, T value) {
            body["params"][key] = value;
        }

    public:
        json jsonify() const;

        std::string stringify() const;

        template <typename T>
        T get_param(const std::string& key) const {
            return body["params"][key].get<T>();
        }

        static request from_string(const std::string& raw);
    };

    class request_builder {
        request req_;
    public:
        request_builder(const std::string& route);

        template <typename T>
        request_builder& set_param(const std::string& key, T value) {
            req_.set_param(key, value);
            return *this;
        }

        request build();
    };

lrrp::request::request() {
    body = json::object();
}

lrrp::request::request(const std::string& raw) {
    body = json::parse(raw);
}

void lrrp::request::set_route(const std::string& route) {
    body["route"] = route;
}

json lrrp::request::jsonify() const{
    return body;
}

std::string lrrp::request::stringify() const {
    return body.dump();
}

lrrp::request lrrp::request::from_string(const std::string& raw) {
    return request(raw);
}

lrrp::request_builder::request_builder(const std::string& route) : req_() {
    req_.set_route(route);
}

lrrp::request lrrp::request_builder::build() {
    return req_;
}

}