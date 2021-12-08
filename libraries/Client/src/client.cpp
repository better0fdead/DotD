#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
//#include <client.hpp>
#include <arpa/inet.h>

using namespace boost::asio;

io_service service;
ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
ip::udp::endpoint ep(ip::address::from_string("178.62.207.127"), 5001);

void send_msg(std::string msg) {

    sock.send_to(buffer(msg), ep);
}

std::string recv_msg() {

    char buff[1024];
    ip::udp::endpoint sender_ep;

    int bytes = sock.receive_from(buffer(buff), sender_ep);

    std::cout << bytes << std::endl;

    std::string copy(buff, bytes);
    std::cout << copy << std::endl;
    return copy;
}

void close_socket() {
    sock.close();
}
