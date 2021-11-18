#pragma once

#include "GameState.hpp"


class Server : public GameState {
public:
    Server();

    ~Server();
//UDP connection in this class
    dateChar resiveDate();  //get data from friend;
    void sendDate(dateChar YourChar);  //send data to friend;

private:
    std::string friendIP;
    dateChar YourChar;
};