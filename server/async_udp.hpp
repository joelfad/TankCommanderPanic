/*
Project:  Server
File:  async_udp.hpp
Author:  Leonardo Banderali
Description:  This file contains an asynchronous UDP echo server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

#ifndef ASYNC_UDP_HPP
#define ASYNC_UDP_HPP

// project headers
#include <char_array.hpp>

// boost libraries
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class async_udp_server {
    public:
        async_udp_server(boost::asio::io_service& io_service, short port);

        void do_receive();

        void do_send(std::size_t length);

    private:
        udp::socket socket_;
        udp::endpoint sender_endpoint_;
        static constexpr std::size_t max_length = 1024;
        char_array<max_length> data_buffer;
};

#endif // ASYNC_UDP_HPP
