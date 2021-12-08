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
//    char buff[1024];
//    ip::udp::endpoint sender_ep;
//    std::cout << "test 1" <<std::endl;
//    int bytes = sock.receive_from(buffer(buff), sender_ep);
//    std::cout << "test 2" <<std::endl;
//
//    std::cout << bytes <<std::endl;
//
//    std::string copy(buff, bytes);
//    std::cout << "test 3" <<std::endl;
//    std::cout << copy <<std::endl;
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

int main(int argc, char *argv[]) {
    char *messages[] = {"0", "1"};
    boost::thread_group threads;
    int i;
    std::string msg0 = "T0 msg to Hero";
    std::string msg1 = "H0 msg to Tyan";
    std::string msg;

    std::cin >> i;
    //threads.create_thread( boost::bind(send_msg, messages[i]));
    //boost::this_thread::sleep( boost::posix_time::millisec(100));
    if (i == 0) {
        send_msg(msg0);
    } else {
        send_msg(msg1);
    }
    i = 10;
    while (true) {
        std::cin >> i;
        if (i == 0) break;
        msg = recv_msg();
    }
    std::cout << msg << std::endl;
    close_socket();
    // threads.join_all();
}