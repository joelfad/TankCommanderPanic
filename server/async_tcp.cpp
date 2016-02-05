/*
Project:  Server
File:  async_tcp.cpp
Author:  Leonardo Banderali
Description:  This file contains an asynchronous TCP echo server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/



// project headers
#include "async_tcp.hpp"

// c++ standard libraries
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>

// boost libraries
#include <boost/filesystem.hpp>



async_tcp_server::async_tcp_server(boost::asio::io_service& io_service, short port) : acceptor(io_service, tcp::endpoint(tcp::v4(), port)), socket(io_service) {
    accept_connections();
}

void async_tcp_server::accept_connections() {
    acceptor.async_accept(socket,
        [this](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "Accepted a connection from " << socket.remote_endpoint().address().to_string()
                          << ":" << socket.remote_endpoint().port() << "\n";
                std::make_shared<tcp_session>(std::move(socket))->start();
            }

            accept_connections();
        });
}



tcp_session::tcp_session(tcp::socket socket) : socket(std::move(socket)) {}

void tcp_session::start() {
    do_read();
}

void tcp_session::do_read() {
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(data_buffer, max_length),
        [this, self](boost::system::error_code error, std::size_t length) {
            if (!error) {
                std::cout << "TCP Client: " << data_buffer << "\n";

                if (data_buffer == "list") {
                    auto current_dir = boost::filesystem::path{"./"};
                    auto message = std::stringstream{};
                    if (boost::filesystem::exists(current_dir)) {
                        auto files = std::stringstream{};
                        files << data_buffer << '\n';

                        // read list of directory items
                        for (auto&& entry : boost::filesystem::directory_iterator(current_dir)) {
                            files << entry.path().filename().string() << '\n';
                        }

                        // add header with the number of bytes of the body
                        auto bytes = std::to_string(files.str().size());

                        // add padding to the header
                        for (int i = bytes.size(); i < 4; i++) {
                            message << '0';
                        }

                        // build the final message and copy it to the buffer
                        message << bytes << files.str();
                        data_buffer.copy(message.str());
                    }

                    // write collected data
                    do_write(std::min(message.str().size(), data_buffer.size()));
                }
                else if (std::regex_match(data_buffer.data(), data_buffer.data()+length, std::regex("get [A-Za-z_ /.]+\\s*"))){
                    boost::filesystem::path file_path("./" + std::string{data_buffer.data()+4, data_buffer.data()+length});

                    std::stringstream message;
                    std::stringstream body;

                    if (boost::filesystem::exists(file_path)) {
                        // read file
                        std::ifstream file;
                        file.open(file_path.string());
                        std::string content;
                        std::getline(file, content, (char)0); // read all lines from file
                        file.close();
                        body << content;
                    }
                    else {
                        body << "Error in openning file " << file_path.string();
                    }

                    // add header with the number of bytes of the body
                    auto bytes = std::to_string(std::min(body.str().size(), max_length - 4));

                    // add padding to the header
                    for (int i = bytes.size(); i < 4; i++) {
                        message << '0';
                    }

                    // build the final message and copy it to the buffer
                    message << bytes << body.str();
                    data_buffer.copy(message.str());

                    // write collected data
                    do_write(std::min(message.str().size(), data_buffer.size()));
                }
                else if (data_buffer == "terminate") {
                    do_write(length);
                    socket.get_io_service().stop();
                }
                else {
                    do_write(length);
                }
            }
        });
}

void tcp_session::do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket, boost::asio::buffer(data_buffer, length),
        [this, self, length](boost::system::error_code error, std::size_t transmitted) {
            if (!error) {
                data_buffer.clear();
                do_read();
            }
        });
}

