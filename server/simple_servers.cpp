/*
Project:  Server
File:  simple_servers.cpp
Author:  Leonardo Banderali
Description:  This is a simple TCP/UDP echoing server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/



// project headers
#include "simple_servers.hpp"

// c++ standard libraries
#include <string>
#include <array>
#include <cstring>
#include <iostream>

// boost libraries
#include <boost/asio.hpp>



//~function implementations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void simple_tcp_server(boost::asio::io_service& io_service, unsigned int port) {
    // make accessing tcp easier
    using boost::asio::ip::tcp;

    // define the maximum length of data to accept
    constexpr int max_data_length = 1024;

    // create an object for accepting tcp connections on a specified port
    auto acceptor = tcp::acceptor{io_service, tcp::endpoint(tcp::v4(), port)};

    // create a socket object for accepting connections
    auto socket = tcp::socket(io_service);

    // accept tcp connections over the socket
    acceptor.accept(socket);

    // display message of new connection
    std::cout << "TCP connection accepted from "<< socket.remote_endpoint().address().to_string()
              << "/" << socket.remote_endpoint().port() << "\n";

    // service the client
    while (true) {
        // a location to store the data sent from the client
        char data[max_data_length];

        // read data sent by the client
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(data), error);

        // if an unexpected error occurred, throw an exception
        if (error && error != boost::asio::error::eof)
            throw boost::system::system_error(error);
        else if (error == boost::asio::error::eof || std::strcmp(data, "logout") == 0) {
            // connection was closed cleanly by client
            std::cout << "Connection was closed by client.\n";
            break;
        }

        // echo the data entered locally
        std::cout << "Received: " << data << "\n";

        // echo the data entered back to the client
        boost::asio::write(socket, boost::asio::buffer(data, length));
    }
}

void simple_udp_server(boost::asio::io_service& io_service, unsigned int port) {
    // make accessing udp easier
    using boost::asio::ip::udp;

    // define the maximum length of data to accept
    constexpr int max_data_length = 1024;

    // create a socket object for accepting connections
    auto socket = udp::socket{io_service, udp::endpoint(udp::v4(), port)};

    // service the client
    while (true) {
        // a location to store the data sent from the client
        //std::array<char, max_data_length> data;
        std::string data;
        data.resize(max_data_length);

        // create an endpoint to be associated with the client's socket
        udp::endpoint sender_endpoint;

        size_t length = socket.receive_from(boost::asio::buffer(const_cast<char*>(data.data()), data.size()), sender_endpoint);
        //boost::asio::async_read(socket, boost::asio::buffer(data));

        // echo the data entered localy
        std::cout << "Received: " << data << "\n";

        // echo the data entered back to the client
        socket.send_to(boost::asio::buffer(data, length), sender_endpoint);
    }
}
