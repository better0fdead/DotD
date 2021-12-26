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
#include <client.hpp>
#include <arpa/inet.h>
#include <client.hpp>
#include "json.hpp"
#include <boost/lexical_cast.hpp>

using namespace boost::asio;
//интерфейс клиента
io_service service;
ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
ip::udp::endpoint ep(ip::address::from_string("178.62.207.127"), 5001);

Client::Client(){};
Client::~Client(){};
//отправка сообщений
nlohmann::json Client::data2json_for_guard(std::vector<Bullet *> bullets, std::vector<std::shared_ptr<Stone>> stones,int teammate,STATES buff){
    nlohmann::json j;
    j["buff"]=buff;
    j["team"]=teammate;
    std::vector<float> vec;
    std::vector<float> vec1;
    std::vector<float> vec2;
    std::vector<float> vec3;
    for(int i=0;i<bullets.size();i++ ){
        vec.push_back(bullets[i]->getPos().x);
        vec1.push_back(bullets[i]->getPos().y);
        vec2.push_back(bullets[i]->direction_x);
        vec3.push_back(bullets[i]->direction_y);
    }
    j["bullet_x"]=vec;
    j["bullet_y"]=vec1;
    j["bullet_dir_x"]=vec2;
    j["bullet_dir_y"]=vec3;
    vec.clear();
    vec1.clear();
    vec2.clear();
    vec3.clear();
    for(int i=0;i<stones.size();i++ ){
        vec.push_back(stones[i]->getPos().x);
        vec1.push_back(stones[i]->getPos().y);
    }
    j["stones_x"]=vec;
    j["stones_y"]=vec1;

    vec.clear();
    vec1.clear();
    return j;
}

data_msg_tyan Client::json2data_for_tyan(nlohmann::json j) {
    data_msg_tyan data_tyan;
    data_tyan.buff=j["buff"];
    data_tyan.team=j["team"];
    return data_tyan;
}
std::vector<float> Client::parse_guard(std::string ss){
    size_t i =1;
    char c1 =ss[i];
    std::vector<float> cur_vec;
    while (c1 != ']'){
        std::string cur1 = "";
        while(c1 != ','){
            cur1 = cur1 + c1 ;
            i++;

            c1=ss[i];

            if(c1== ']'){
                break;
            }
        }
        cur_vec.push_back(std::stod(cur1));
        if(c1== ']'){
            break;
        }
        i++;
        c1=ss[i];
    }
    return cur_vec;
}
data_msg_guard Client::json2data_for_guard(nlohmann::json j) {
    data_msg_guard data_guard;
    data_guard.buff = j["buff"];
    std::string s1 = j["bullet_x"].dump();
    std::string s2 = j["bullet_y"].dump();
    std::string s3 = j["stones_x"].dump();
    std::string s4 = j["stones_y"].dump();
    std::string s5 = j["bullet_dir_x"].dump();
    std::string s6 = j["bullet_dir_y"].dump();
    data_guard.bullets_x = parse_guard(s1);
    data_guard.bullets_y = parse_guard(s2);
    data_guard.stones_x = parse_guard(s3);
    data_guard.stones_y = parse_guard(s4);
    data_guard.bullets_dir_x = parse_guard(s5);
    data_guard.bullets_dir_y = parse_guard(s6);
    return data_guard;
}


nlohmann::json Client::data2json_for_tyan(int teammate,int buff) {
    nlohmann::json j;
    j["team"]= teammate;
    j["buff"]=buff;
    return j;
}

void Client::send_msg_to_tyan(std::vector<Bullet *> bullets, std::vector<std::shared_ptr<Stone>> stones,int teammate, STATES buff){
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
    char buff[2048];
    ip::udp::endpoint sender_ep;
    int bytes = sock.receive_from(buffer(buff), sender_ep);
    std::string copy(buff, bytes);
    nlohmann::json j= nlohmann::json::parse(copy);
    return json2data_for_tyan(j);
}

struct data_msg_guard Client::recv_msg_from_guard() {

    char buff[2048];
    ip::udp::endpoint sender_ep;
    int bytes = sock.receive_from(buffer(buff), sender_ep);
    std::string copy(buff, bytes);
    nlohmann::json j= nlohmann::json::parse(copy);
    return json2data_for_guard(j);
}
void Client::send_msg(const std::string& msg) {

    sock.send_to(buffer(msg), ep);
}
//прием сообщений
std::string Client::recv_msg() {

    char buff[2048];
    ip::udp::endpoint sender_ep;

    int bytes = sock.receive_from(buffer(buff), sender_ep);


    std::string copy(buff, bytes);
    if (copy[0]!='0') {
        std::cout << copy << std::endl; //вывод в консоль
    }
    return copy;
}


void Client::close_socket() {
    sock.close();
}
//простейший udp клиент
