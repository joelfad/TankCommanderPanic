/*
Project:  Tank Commander Panic
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
            // request input from user
            std::cout << "Please enter a message to be sent to the server ('logout' to terminate): ";
            char_array<max_length> request;
            std::cin.getline(request.data(), request.size());
            size_t request_length = request.length();

            // send message to the server
            boost::asio::write(s, boost::asio::buffer(request, request_length));

            // handle quit messages
            if (request == "logout" || request == "terminate") {
                break;
            }

            // get header from server
            char_array<5> header;
            boost::asio::read(s, boost::asio::buffer(header, header.size()));
            int bytes = std::stoi(std::string{header.data(), header.data()+4} + "\0");
            int status_code = std::stoi(std::string{header.data()+4,header.data()+5} + "\0");
            char_array<max_length> reply;
            size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply.data(), bytes));

            // handle specific server responses based on entered commands
            if (request == "list") {
                std::cout.write(reply.data(), reply_length);
                std::cout.flush();
            }
            else if (std::regex_match(request.data(), request.data()+request_length, std::regex("get [A-Za-z_ /.]+\\s*"))) {
                if (status_code == 0) {
                    std::stringstream file_name;
                    file_name << std::string{request.data()+4, request.data()+request_length}
                              << "-" <<  s.local_endpoint().port();
                    std::ofstream file;
                    file.open(file_name.str());
                    file.write(reply.data(), reply_length);
                    file.flush();
                    file.close();
                    std::cout << "File saved in " << file_name.str() << " (" << reply_length << " bytes)\n";
                }
                else {
                    std::cout.write(reply.data(), reply_length);
                    std::cout.flush();
                }
            }
            else {
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
