#pragma once
#include <string>

#include <nlohmann/json.hpp>

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

    public:
        void set_payload(const json& payload);
        void set_status(status_type status);

        json jsonify();
        std::string stringify();

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
}
