
#include <client.hpp>


//интерфейс клиента
boost::asio::io_service service;
boost::asio::ip::udp::socket sock(service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
boost::asio::ip::udp::endpoint ep(boost::asio::ip::address::from_string("178.62.207.127"), 5001);

Client::Client(){};
Client::~Client(){};
//отправка сообщений
nlohmann::json Client::data2json_for_guard(std::vector<Bullet *> bullets, std::vector<std::shared_ptr<Stone>> stones,int teammate,STATES buff,int score){
    nlohmann::json j;
    j["score"]=score;
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
        vec2.push_back(stones[i]->size);
    }
    j["stones_x"]=vec;
    j["stones_y"]=vec1;
    j["stones_size"]=vec2;

    vec.clear();
    vec2.clear();
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
    data_guard.score = j["score"];

    std::string s1 = j["bullet_x"].dump();
    data_guard.bullets_x = parse_guard(s1);
    s1 = j["bullet_y"].dump();
    data_guard.bullets_y = parse_guard(s1);
    s1 = j["stones_x"].dump();
    data_guard.stones_x = parse_guard(s1);
    s1 = j["stones_y"].dump();
    data_guard.stones_y = parse_guard(s1);

    s1 = j["bullet_dir_x"].dump();
    data_guard.bullets_dir_x = parse_guard(s1);

    s1 = j["bullet_dir_y"].dump();
    data_guard.bullets_dir_y = parse_guard(s1);

    s1 = j["stones_size"].dump();
    data_guard.stones_size = parse_guard(s1);

    return data_guard;
}


nlohmann::json Client::data2json_for_tyan(int teammate,int buff) {
    nlohmann::json j;
    j["team"]= teammate;
    j["buff"]=buff;
    return j;
}

void Client::send_msg_to_tyan(std::vector<Bullet *> bullets, std::vector<std::shared_ptr<Stone>> stones,int teammate, STATES buff,int score){
    nlohmann::json j =data2json_for_guard(bullets,stones,teammate,buff,score);
    std::string msg = j.dump();
    sock.send_to(boost::asio::buffer(msg), ep);
}
void Client::send_msg_to_guard(int teammate,int buff){
    nlohmann::json j =data2json_for_tyan(teammate,buff);
    std::string msg = j.dump();
    sock.send_to(boost::asio::buffer(msg), ep);
}


struct data_msg_tyan Client::recv_msg_from_tyan() {
    char buff[2048];
    boost::asio::ip::udp::endpoint sender_ep;
    int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);
    std::string copy(buff, bytes);
    nlohmann::json j= nlohmann::json::parse(copy);
    return json2data_for_tyan(j);
}

struct data_msg_guard Client::recv_msg_from_guard() {

    char buff[2048];
    boost::asio::ip::udp::endpoint sender_ep;
    int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);
    std::string copy(buff, bytes);
    nlohmann::json j= nlohmann::json::parse(copy);
    return json2data_for_guard(j);
}
void Client::send_msg(const std::string& msg) {

    sock.send_to(boost::asio::buffer(msg), ep);
}
//прием сообщений
std::string Client::recv_msg() {

    char buff[2048];
    boost::asio::ip::udp::endpoint sender_ep;

    int bytes = sock.receive_from(boost::asio::buffer(buff), sender_ep);


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
