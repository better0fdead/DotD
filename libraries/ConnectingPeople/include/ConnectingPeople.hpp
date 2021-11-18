#pragma once

#include "ConnectingState.hpp"


class ConnectingPeople : public ConnectingState {
public:
    ConnectingPeople();

    ~ConnectingPeople();
//TCP connection in this class
    void sendIP(bool role);  //send IP to server;
    string waitngPeople();  //get IP from server;

};