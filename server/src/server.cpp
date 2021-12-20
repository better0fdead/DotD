#include <server.hpp>

constexpr char param_con = '1';
constexpr char param_buff = '2';
constexpr char param_death = '3';
constexpr char tyan = 'T';
constexpr char hero = 'H';
int *flag_t = new int(0);
int *flag_h = new int(0);
boost::asio::ip::udp::endpoint Tyans[3];
boost::asio::ip::udp::endpoint Heros[3];
boost::asio::io_service service;

//void handler(const boost::system::error_code& e, size_t bytes);
void signal_handler(int signum){
    delete flag_t;
    delete flag_h;
    exit(signum);
};

char parse_msg(std::string msg,int *flag,boost::asio::ip::udp::endpoint sender_ep) {
    char parametr = msg[3];
    char parametr_ans;
    if (parametr == param_con) {
        flag = 1;
        if (msg[0] == tyan) Tyans[0] = sender_ep; else Heros[0] = sender_ep;
        parametr_ans = parametr;

    } else if (parametr == param_buff) {
        parametr_ans = msg[5];
        if (!(parametr_ans == '0')) {
            std::cout << "Ans:" << parametr_ans << std::endl;
        }
    }
    return parametr_ans;
}

void handle_connections() {
    boost::asio::ip::udp::socket sock(service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 5001));
    char buff[1024];
    //две очереди игроков

    //Тут я вручную делаю пару, но должна быть очередь
    int index_tyan = 0;
    int index_hero = 0;
    std::string tyan_msg;
    std::string hero_msg;
    int flag_connection = 1;
    char parametr_t_ans;
    char parametr_h_ans;
    std::string tyan_ans;
    std::string hero_ans;

    while (true) {
        boost::asio::ip::udp::endpoint sender_ep;
        std::cout <<"Жду приема информации"<<std::endl;
        int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);
        std::string msg(buff, bytes);
        std::cout <<msg<<std::endl;
        std::cout <<msg[0]<<std::endl;

        if (msg[0] == tyan) parametr_t_ans = parse_msg(msg, flag_t, sender_ep);
        else if((msg[0] == hero)) parametr_h_ans = parse_msg(msg, flag_h, sender_ep);

        std::cout <<"Прошел парсинг"<<std::endl;

        if (*flag_t && *flag_h && flag_connection) {
            std::cout <<"Зашел в конекшон"<<std::endl;

            tyan_ans = param_con;
            hero_ans = param_con;
            sock.send_to(boost::asio::buffer(tyan_ans), Tyans[0]);
            sock.send_to(boost::asio::buffer(hero_ans), Heros[0]);
            flag_connection = 0;
            std::cout << "Clients connect" << std::endl;

        }
        //данные которые отправляются парой
        if (!flag_connection) {
            std::cout <<"Зашел в отправку"<<std::endl;

            hero_ans = parametr_h_ans;
            tyan_ans = parametr_t_ans;
            sock.send_to(boost::asio::buffer(tyan_ans), Heros[0]);
            sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
            parametr_t_ans = '0';

        }
    }

}

//В итоге получилось, что я реализовал имитацию асинхронного сервера.
// В следующей версии надеюсь будет нормальный асинхр. tyan_ansУ меня уже есть бета версия, но проблемы с передачей структуры данных, а не строки.