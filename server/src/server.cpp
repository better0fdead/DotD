
#include <server.hpp>

struct Response {
    int status_hero;
    std::vector<int> stones;
};
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
void signal_handler(int signum) {
    delete flag_t;
    delete flag_h;
    exit(signum);
};

char parse_msg_con(std::string msg, int *flag, boost::asio::ip::udp::endpoint sender_ep) {
    char parametr = msg[3];
    char parametr_ans;
    if (parametr == param_con) {
        *flag = 1;
        if (msg[0] == tyan) Tyans[0] = sender_ep; else Heros[0] = sender_ep;
        parametr_ans = parametr;

    }
//    else if (parametr == param_buff) {
//        parametr_ans = msg[5];
//        if (!(parametr_ans == '0')) {
//            std::cout << "Ans:" << parametr_ans << std::endl;
//        }
//    }
    return parametr_ans;
}


void handle_connections() {
    boost::asio::ip::udp::socket sock(service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 5001));
    char buff[1024];

    int index_tyan = 0;
    int index_hero = 0;
    std::string tyan_msg;
    std::string hero_msg;
    int flag_connection = 1;
    char parametr_t_ans;
    char parametr_h_ans;
    std::string tyan_ans;
    std::string hero_ans;
    std::string msg;
    std::string ss;
    int a;
    while (true) {
        boost::asio::ip::udp::endpoint sender_ep;
        std::cout << "Жду приема информации" << std::endl;
        int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);
        std::string msg(buff, bytes);
        std::cout << msg << std::endl;

        std::cout << "flag_t " << *flag_t << std::endl;
        std::cout << "flag_h " << *flag_h << std::endl;
        if (msg[0] == tyan) parametr_t_ans = parse_msg_con(msg, flag_t, sender_ep);
        else if ((msg[0] == hero)) parametr_h_ans = parse_msg_con(msg, flag_h, sender_ep);
        else if ((!flag_connection)) {

            std::cout << "Зашел в отправку" << std::endl;
            nlohmann::json j = nlohmann::json::parse(msg);
            std::cout << "team " << j["team"] << std::endl;
            a = j["team"];
            if (a == 1) {
                tyan_ans = msg;
                std::cout << "TYAN SEND" << std::endl;
                std::cout << "buff " << j["buff"] << std::endl;
                std::cout << "buff " << j["buff"] << std::endl;
                std::cout << "team " << j["team"] << std::endl;
                sock.send_to(boost::asio::buffer(tyan_ans), Heros[0]);
                if (hero_msg != "") {
                    sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
                }
            } else {
                hero_ans = msg;
                std::cout << "GUARD SEND" << std::endl;
                ss = j["bullet_x"].dump();
                std::cout << "bullets: " << ss << std::endl;
                if (tyan_msg != "") {
                    sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
                }
                sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
            }
        }

        std::cout << *flag_t << std::endl;
        std::cout << *flag_h << std::endl;

        if (*flag_t && *flag_h && flag_connection) {
            std::cout << "Зашел в конекшoн" << std::endl;

            tyan_ans = param_con;
            hero_ans = param_con;
            sock.send_to(boost::asio::buffer("1"), Tyans[0]);
            sock.send_to(boost::asio::buffer("1"), Heros[0]);

            flag_connection = 0;
            std::cout << "Clients connect" << std::endl;

        }

        if (*flag_t && !flag_connection) {
            std::cout << "Тянка ждет гарда" << std::endl;

            sock.send_to(boost::asio::buffer("0"), Tyans[0]);

        }
        if (*flag_h && !flag_connection) {
            std::cout << "Гард ждет тянку" << std::endl;

            sock.send_to(boost::asio::buffer("0"), Heros[0]);

        }
        //данные которые отправляются парой
//        if ((!flag_connection) && (msg[0] != 'T') && (msg[0] != 'H')) {
//
//            std::cout << "Зашел в отправку" << std::endl;
//            nlohmann::json j= nlohmann::json::parse(msg);
//            std::cout << "team " << j["team"] << std::endl;
//            a = j["team"];
//            if (a == 1) {
//                tyan_ans = msg;
//                std::cout << "TYAN SEND"  <<std::endl;
//                std::cout << "buff " << j["buff"] << std::endl;
//                std::cout << "buff " << j["buff"] << std::endl;
//                std::cout << "team " << j["team"] << std::endl;
//                sock.send_to(boost::asio::buffer(tyan_ans), Heros[0]);
//                if (hero_msg != "") {
//                    sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
//                }
//            }else{
//                hero_ans = msg;
//                std::cout << "GUARD SEND"  <<std::endl;
//                ss = j["bullet_x"].dump();
//                std::cout << "bullets: "  << ss << std::endl;
//                if (tyan_msg != "") {
//                    sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
//                }
//            sock.send_to(boost::asio::buffer(hero_ans), Tyans[0]);
//        }
//    }

    }
}

//В итоге получилось, что я реализовал имитацию асинхронного сервера.
// В следующей версии надеюсь будет нормальный асинхр. tyan_ansУ меня уже есть бета версия, но проблемы с передачей структуры данных, а не строки.