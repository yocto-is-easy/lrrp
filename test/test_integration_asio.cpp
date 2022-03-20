#include "gtest/gtest.h"

#include "boost/asio.hpp"

using namespace boost;

TEST(asio, test1)
{
    asio::io_context context_;
    asio::ip::tcp::socket socket_(context_);
    std::cout << socket_.max_connections << std::endl;
}
