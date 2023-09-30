#pragma once
#include <string>

#include <nlohmann/json.hpp>

#include "base64.h"

using namespace nlohmann;

namespace lrrp
{
    enum status_type
    {
        ok,
        internal_error,
        user_error
    };

    class response
    {
        json body;

        friend class response_builder;

        response();
        response(const std::string& raw);

        void set_payload(const json& payload);
        void set_status(status_type status);
    public:
        json jsonify() const;
        std::string stringify() const;

        json get_payload();

        static response from_string(const std::string& raw);
    };

    class response_builder
    {
        response res_;
    public:
        response_builder();

        response_builder& set_payload(const json& payload);
        response_builder& set_status(const status_type& status);

        response build();
    };

lrrp::response_builder::response_builder() {
    res_ = response();
}

lrrp::response_builder& lrrp::response_builder::set_payload(const json& payload) {
    res_.set_payload(payload);
    return *this;
}

lrrp::response_builder& lrrp::response_builder::set_status(const status_type& status) {
    res_.set_status(status);
    return *this;
}

lrrp::response lrrp::response_builder::build() {
    return res_;
}

lrrp::response::response() {
    body = json::object();
}

lrrp::response::response(const std::string& raw) {
    body = json::parse(raw);
}

void lrrp::response::set_payload(const json& payload) {
    body["payload"] = payload;
}

void lrrp::response::set_status(status_type status) {
    body["status"] = status;
}

json lrrp::response::jsonify() const {
    return body;
}

std::string lrrp::response::stringify() const {
    return base64::encode(body.dump());
}

lrrp::response lrrp::response::from_string(const std::string& raw) {
    return response(base64::decode(raw));
}

json lrrp::response::get_payload() {
    return body["payload"];
}

}
