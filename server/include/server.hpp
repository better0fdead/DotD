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
#include <csignal>
#include <vector>
#include <json.hpp>

void handle_connections();
int main(int argc, char* argv[]);
void signal_handler(int signum);