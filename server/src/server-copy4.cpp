#include <server.hpp>
#include <arpa/inet.h>
using namespace boost::asio;
using namespace boost::posix_time;

io_service service;
void handler(const boost::system::error_code& e, size_t bytes);

void handle_connections() {
    char buff[1024];
    ip::udp::endpoint Tyans[3];
    ip::udp::endpoint Heros[3];
    ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 5001));
    int index_tyan = 0;
    int index_hero = 0;
    int flag_t = 0;
    int flag_h = 0;
    std::string tyan_msg;
    std::string hero_msg;
    int flag_connection = 1;
    char parametr_t_ans = '0';
    char parametr_h_ans = '0';
    std::string tyan_ans ="0";
    std::string hero_ans ="0";
    while (true) {
        ip::udp::endpoint sender_ep;
        int bytes = sock.receive_from(buffer(buff), sender_ep);
        std::string msg(buff, bytes);
        for(int i = 0; i < msg.size();i++){
            char c = msg[i];


            if(i == 0){

                if(c == 'T'){

                    char parametr_t =msg[i+3];
                    if (parametr_t == '1'){
                        flag_t = 1;
                    }else if (parametr_t == '2'){
                        parametr_t_ans =msg[i+5];
                        if (!(parametr_t_ans =='0') ) {
                            std::cout << "Ans:" << parametr_t_ans << std::endl;
                        }
                        break;
                    }
                Tyans[0]=sender_ep;
                tyan_msg = msg;
                    break;
                }
                if( c == 'H'){
                    std::cout << "msg hero:" << msg << std::endl;

                    char parametr_h =msg[i+3];
                    if (parametr_h == '1'){
                        flag_h = 1;
                    }else if (parametr_h == '3'){
                        parametr_h_ans =msg[i+5];
                        if (!(parametr_h_ans =='0') ) {
                            std::cout << "Game:" << parametr_t_ans << std::endl;
                        }
                        break;
                    }
                    Heros[0]=sender_ep;
                    hero_msg = msg;
                    flag_h = 1;
                    break;
                }
            }

        }

        if (flag_t && flag_h && flag_connection) {
            sock.send_to(buffer("1"), Tyans[0]);
            sock.send_to(buffer("1"), Heros[0]);
            flag_connection = 0;
        }
        if (!flag_connection){
            hero_ans=parametr_h_ans;
            tyan_ans=parametr_t_ans;
            sock.send_to(buffer(tyan_ans), Heros[0]);
            sock.send_to(buffer(hero_ans), Tyans[0]);
            parametr_t_ans = '0';

        }
    }

}

int main(int argc, char* argv[]) {
    handle_connections();
}