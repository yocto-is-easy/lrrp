#pragma once

#include <string>

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/detail/base64.hpp>

namespace lrrp
{

class base64 {
public:
    static std::string encode(const std::string& data);
    static std::string decode(const std::string& data);
};

std::string base64::encode(const std::string& input) {
    std::string out(boost::beast::detail::base64::encoded_size(input.size()), '\0');
    int len = boost::beast::detail::base64::encode((void*)out.data(), (const char*)input.data(), input.size());
    out.resize(len);
    return out;
}

std::string base64::decode(const std::string& input) {
    std::string out(boost::beast::detail::base64::decoded_size(input.size()), '\0');
    auto len = boost::beast::detail::base64::decode((void*)out.data(), (const char*)input.data(), input.size());
    out.resize(len.first);
    return out;
}

} // namespace lrrp
