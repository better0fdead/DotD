#pragma once
#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <arpa/inet.h>


class Client  {
public:
    Client();
    ~Client();
    void send_msg(const std::string& msg);
    std::string recv_msg();
    void close_socket();


};
