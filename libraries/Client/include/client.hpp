#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>

//void close_socket();
//std::string recv_msg();
//void send_msg(std::string msg);

class Client  {
public:
    Client();
    ~Client();
    void send_msg(std::string msg);
    std::string recv_msg();
    void close_socket();


};
