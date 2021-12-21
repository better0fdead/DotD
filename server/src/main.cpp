#include <server.hpp>

int main(int argc, char *argv[]) {
    signal(SIGINT,signal_handler);
    handle_connections();
}
