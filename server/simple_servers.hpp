/*
Project:  Tank Commander Panic
File:  simple_servers.hpp
Author:  Leonardo Banderali
Description:  This is a simple TCP/UDP echoing server.
Notes:  Code was inspired from some examples provided with the Boost.Asio library.
    (http://www.boost.org/doc/libs/1_60_0/doc/html/boost_asio/examples/cpp11_examples.html)
*/

#ifndef SIMPLER_SERVERS_HPP
#define SIMPLER_SERVERS_HPP



// boost libraries
#include <boost/asio.hpp>



//~function declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void simple_tcp_server(boost::asio::io_service& io_service, unsigned int port);

void simple_udp_server(boost::asio::io_service& io_service, unsigned int port);

#endif // SIMPLER_SERVERS_HPP
