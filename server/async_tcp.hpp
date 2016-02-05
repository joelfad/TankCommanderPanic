/*
Project:  Server
File:  async_tcp.hpp
Author:  Leonardo Banderali
Description:  This file contains an asynchronous TCP echo server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

#ifndef ASYNC_TCP_HPP
#define ASYNC_TCP_HPP



// project headers
#include "char_array.hpp"

// boost libraries
#include <boost/asio.hpp>



// make accessing tcp easyier
using boost::asio::ip::tcp;

class tcp_session : public std::enable_shared_from_this<tcp_session> {
    public:
        tcp_session(tcp::socket socket);

        void start();

    private:
        void do_read();

        void do_write(std::size_t length);

        tcp::socket socket;
        static constexpr std::size_t max_length = 1024;
        char_array<max_length> data_buffer;
};

class async_tcp_server {
    public:
        async_tcp_server(boost::asio::io_service& io_service, short port);

    private:
        void accept_connections();

        tcp::acceptor acceptor;
        tcp::socket socket;
};

#endif // ASYNC_TCP_HPP
