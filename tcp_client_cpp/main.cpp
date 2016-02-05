/*
Project:  Server
File:  main.cpp
Author:  Leonardo Banderali
Description:  This is a simple TCP client to work with the provided TCP/UDP server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

#include <char_array.hpp>

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

constexpr std::size_t max_length = 1024;

int main(int argc, char* argv[]) {

    if (argc != 3)
    {
      std::cerr << "Usage: tcp_client_cpp <host> <port>\n";
      return 1;
    }

    try {
        boost::asio::io_service io_service;

        tcp::socket s(io_service);
        tcp::resolver resolver(io_service);
        boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));

        while (true) {
            std::cout << "Enter message: ";
            char_array<max_length> request;
            std::cin.getline(request.data(), request.size());
            size_t request_length = request.length();

            if (request == "logout") {
                break;
            }
            else if (request == "list") {
                boost::asio::write(s, boost::asio::buffer(request, request_length));

                char_array<5> byte_count;
                boost::asio::read(s, boost::asio::buffer(byte_count, byte_count.size() - 1));
                byte_count.set_null(4); // add null terminator
                int bytes = std::stoi(std::string(byte_count.data()));
                char_array<max_length> reply;
                size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply.data(), bytes));
                std::cout.write(reply.data(), reply_length);
                std::cout.flush();
            }
            else if (std::regex_match(request.data(), request.data()+request_length, std::regex("get [A-Za-z_ /.]+\\s*"))) {
                boost::asio::write(s, boost::asio::buffer(request, request_length));

                char_array<5> byte_count;
                boost::asio::read(s, boost::asio::buffer(byte_count, byte_count.size() - 1));
                byte_count.set_null(4); // add null terminator
                int bytes = std::stoi(std::string(byte_count.data()));
                char_array<max_length> reply;
                size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply.data(), bytes));
                std::string file_name = std::string{request.data()+4, request.data()+request_length} + "-" + std::string(argv[2]);
                std::ofstream file;
                file.open(file_name);
                file.write(reply.data(), reply_length);
                file.flush();
                file.close();
                std::cout << "File saved in " << file_name << "(" << reply_length << " bytes)\n";
            }
            else if (request == "terminate") {
                boost::asio::write(s, boost::asio::buffer(request, request_length));
                break;
            }
            else {
                boost::asio::write(s, boost::asio::buffer(request, request_length));

                char_array<5> byte_count;
                boost::asio::read(s, boost::asio::buffer(byte_count, byte_count.size() - 1));
                byte_count.set_null(4); // add null terminator
                int bytes = std::stoi(std::string(byte_count.data()));
                char_array<max_length> reply;
                size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply.data(), bytes));
                std::cout.write(reply.data(), reply_length);
                std::cout.flush();
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
