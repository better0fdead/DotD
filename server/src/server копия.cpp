#include <server.hpp>
#include <arpa/inet.h>
using namespace boost::asio;
using namespace boost::posix_time;

io_service service;

void handle_connections() {
//    char** messages = new char * [2];
//    for (int j = 0; j < 2; ++j )
//        messages[j] = new char[100];
//    size_t size_buf = sizeof(messages);

    ip::udp::endpoint senders[3];
    ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 5001));
    char** messages = new char * [2];
    for (int j = 0; j < 2; ++j )
        messages[j] = new char[100];

    size_t size_buf = sizeof(messages);
    mutable_buffer buff(messages,16);
    std::cout << buff.size()<<std::endl;

    while (true) {
        ip::udp::endpoint sender_ep;
        int bytes =sock.receive_from(buffer(buff), sender_ep);
        std::cout << "aue"<<std::endl;
        std::cout << buff.size()<<std::endl;
        char** p2 = (char **) buff.data();
        std::cout << bytes<<std::endl;
        std::cout << "aue"<<std::endl;
        std::cout << p2[0]<<std::endl;

//        if (msg == "1"){
//            senders[0]= sender_ep;
//        }
//        if (msg == "2"){
//            senders[1]= sender_ep;
//            std::cout << "davai"<<std::endl;
//            std::cout << senders[0]<<std::endl;
//            std::cout << sender_ep<<std::endl;
//
//            sock.send_to(buffer("teeeeestingg"), senders[0]);
//            sock.send_to(buffer("test"), sender_ep);
//        }

    }

}
int main(int argc, char* argv[]) {
    handle_connections();
}