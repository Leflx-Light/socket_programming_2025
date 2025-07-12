// client.h
#pragma once

#include <string>

class Client {
public:
    Client(const std::string& host, int port);
    ~Client();

    void run();

private:
    int sock_fd;
    std::string host;
    int port;

    void setup_connection();
    void communicate();
};
