#include <client.hpp>
#include <json.hpp>

using namespace boost::asio;
//интерфейс клиента
io_service service;
ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
ip::udp::endpoint ep(ip::address::from_string("178.62.207.127"), 5001);

Client::Client(){};
Client::~Client(){};
//отправка сообщений
void Client::send_msg(const std::string& msg) {

    sock.send_to(buffer(msg), ep);
}
//прием сообщений
std::string Client::recv_msg() {

    char buff[1024];
    ip::udp::endpoint sender_ep;

    int bytes = sock.receive_from(buffer(buff), sender_ep);


    std::string copy(buff, bytes);
    if (copy!="0") {
        std::cout << copy << std::endl; //вывод в консоль
    }
    return copy;
}

void Client::close_socket() {
    sock.close();
}
//простейший udp клиент
