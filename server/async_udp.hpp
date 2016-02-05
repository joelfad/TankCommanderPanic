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

#include <iostream>
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
        enum { max_length = 1024 };
        char data_[max_length];
};

#endif // ASYNC_UDP_HPP
