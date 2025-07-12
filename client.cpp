#include "client.h"

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<thread>
#include<chrono>

Client::Client(const std::string& host, int port)
    : host(host), port(port), sock_fd(-1) {}

Client::~Client() {
    if (sock_fd != -1) close(sock_fd);
}

void Client::run() {
    setup_connection();
    communicate();
}

void Client::setup_connection() {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        perror("Invalid address / not supported");
        exit(EXIT_FAILURE);
    }

    while (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("⚠️ Connection failed — retrying...");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "🔗 Connected to server " << host << ":" << port << "\n";
}

void Client::communicate() {
    std::string msg;
    std::cout << "✍️ Enter message to send to server: ";
    std::getline(std::cin, msg);

    if (msg.empty()) msg = "(empty message)";

    send(sock_fd, msg.c_str(), msg.size(), 0);

    char buffer[1024] = {0};
    int bytes_read = read(sock_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        std::cout << "📨 Received from server: " << buffer << "\n";
    }
}
