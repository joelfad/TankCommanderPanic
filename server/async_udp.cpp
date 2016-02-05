/*
Project:  Server
File:  async_udp.cpp
Author:  Leonardo Banderali
Description:  This file contains an asynchronous UDP echo server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/



// project headers
#include "async_udp.hpp"



async_udp_server::async_udp_server(boost::asio::io_service& io_service, short port) : socket_(io_service, udp::endpoint(udp::v4(), port)) {
    do_receive();
}

void async_udp_server::do_receive() {
    socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                std::cout << "UDP Client: " << data_;
                do_send(bytes_recvd);
            }
            else {
                do_receive();
            }
        });
}

void async_udp_server::do_send(std::size_t length) {
    socket_.async_send_to(boost::asio::buffer(data_, length), sender_endpoint_,
        [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            do_receive();
        });
}
