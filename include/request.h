#pragma once
#include <string>
#include <map>

#include <nlohmann/json.hpp>

using namespace nlohmann;

namespace lrrp
{
    class request {
        json body;
    public:
        request();
        void set_route(const std::string& route);

        // here can be set any base type or json object
        template <typename T>
        void set_param(const std::string& key, T value) {
            body["params"][key] = value;
        }

        json jsonify();

        std::string stringify();
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
}