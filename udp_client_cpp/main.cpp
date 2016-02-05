/*
Project:  Server
File:  main.cpp
Author:  Joel McFadden
Description:  This is a simple TCP client to work with the provided TCP/UDP server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

// project headers
#include <char_array.hpp>

// c++ standard libraries
#include <iostream>

// boost libraries
#include <boost/asio.hpp>

using boost::asio::ip::udp;

constexpr std::size_t max_length = 1024;

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: udp_client_cpp <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

        udp::resolver resolver(io_service);
        udp::endpoint endpoint = *resolver.resolve({udp::v4(), argv[1], argv[2]});

        while (true) {
            std::cout << "Please enter a message to be sent to the server ('logout' to terminate): ";
            char_array<max_length> request;
            std::cin.getline(request.data(), max_length);
            if (request == "logout")
                break;
            size_t request_length = request.length();
            s.send_to(boost::asio::buffer(request, request_length), endpoint);

            char_array<max_length> reply;
            udp::endpoint sender_endpoint;
            size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
            std::cout << "Server: ";
            std::cout.write(reply.data(), reply_length);
            std::cout << "\n";
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
