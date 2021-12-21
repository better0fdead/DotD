#pragma once
#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <arpa/inet.h>
#include "Bullet.hpp"
#include "Stone.hpp"
#include "json.hpp"
#include "GameContext.hpp"

struct data_msg_guard
{
    int team;
    int buff;
    std::vector<Bullet *> bullets;
    std::vector<Stone *> stones;
};

struct data_msg_tyan
{
    int team;
    int buff;
};

class Client  {
public:
    Client();
    ~Client();
    void close_socket();

    void send_msg(const std::string &msg);

    std::string recv_msg();

    data_msg_tyan recv_msg_from_tyan();

    void send_msg_to_guard(int teammate, int buff);

    void send_msg_to_tyan(std::vector<Bullet *> bullets, std::vector<std::shared_ptr<Stone>> stones, int teammate, STATES buff);

    nlohmann::basic_json<> data2json_for_tyan(int teammate, int buff);

    data_msg_tyan json2data_for_tyan(nlohmann::json j);

    nlohmann::json
    data2json_for_guard(std::vector<Bullet *> bullets, std::vector<std::shared_ptr<Stone>> stones, int teammate, STATES buff);
};


