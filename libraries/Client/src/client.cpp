#include <client.hpp>
#include "json.hpp"


using namespace boost::asio;
//интерфейс клиента
io_service service;
ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
ip::udp::endpoint ep(ip::address::from_string("178.62.207.127"), 5001);

Client::Client(){};
Client::~Client(){};
//отправка сообщений
nlohmann::json Client::data2json_for_guard(std::vector<Bullet *> bullets, std::vector<Stone *> stones,int teammate,int buff){
    nlohmann::json j;
    j["buff"]=buff;
    j["team"]=teammate;
    std::vector<float> vec;
    std::vector<float> vec1;
    std::vector<float> vec2;

    for(int i=0;i<bullets.size();i++ ){
        vec.push_back(bullets[i]->getPos().x);
        vec1.push_back(bullets[i]->getPos().y);
        vec2.push_back(bullets[i]->getPos().y);
    }
    j["bullet_x"]=vec;
    j["bullet_y"]=vec1;
    vec.clear();
    vec1.clear();
    for(int i=0;i<stones.size();i++ ){
        vec.push_back(stones[i]->getPos().x);
        vec1.push_back(stones[i]->getPos().y);
        vec2.push_back(stones[i]->getPos().y);
    }
    j["stones_x"]=vec;
    j["stones_y"]=vec1;
    vec.clear();
    vec1.clear();
    return j;
}

data_msg_tyan Client::json2data_for_tyan(nlohmann::json j) {
    data_msg_tyan data_tyan;
    std::string msg = j["buff"].dump();
    data_tyan.buff=msg[1];
    msg = j["team"].dump();
    data_tyan.team=msg[1];
    return data_tyan;
}


nlohmann::json Client::data2json_for_tyan(int teammate,int buff) {
    nlohmann::json j;
    j["team"]= teammate;
    j["buff"]=buff;
    return j;
}

void Client::send_msg_to_tyan(std::vector<Bullet *> bullets, std::vector<Stone *> stones,int teammate,int buff){
    nlohmann::json j =data2json_for_guard(bullets,stones,teammate,buff);
    std::string msg = j.dump();
    sock.send_to(buffer(msg), ep);
}
void Client::send_msg_to_guard(int teammate,int buff){
    nlohmann::json j =data2json_for_tyan(teammate,buff);
    std::string msg = j.dump();
    sock.send_to(buffer(msg), ep);
}


struct data_msg_tyan Client::recv_msg_from_tyan() {
    char buff[1024];
    ip::udp::endpoint sender_ep;
    int bytes = sock.receive_from(buffer(buff), sender_ep);
    nlohmann::json j= nlohmann::json::parse(buff);
    return json2data_for_tyan(j);
}
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
