#pragma once

#include <string>

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/algorithm/string.hpp>

namespace lrrp
{

class base64 {
public:
    static std::string encode(const std::string& data);
    static std::string decode(const std::string& data);
};

std::string base64::encode(const std::string& data) {
    using namespace boost::archive::iterators;
    using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
    return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(data)), It(std::end(data))), [](char c) {
        return c == '\0';
    });
}

std::string base64::decode(const std::string& data) {
    using namespace boost::archive::iterators;
    using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto tmp = std::string(It(std::begin(data)), It(std::end(data)));
    return tmp.append((3 - data.size() % 3) % 3, '=');
}

} // namespace lrrp
