#include "server.h"

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <chrono>

TcpServer::TcpServer(int port)
    : port(port), server_fd(-1), client_fd(-1) {}

TcpServer::~TcpServer() {
    if (client_fd != -1) close(client_fd);
    if (server_fd != -1) close(server_fd);
}

void TcpServer::run() {
    setup_socket();
    accept_client();
    communicate();
}

void TcpServer::setup_socket() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "✅ Server listening on port " << port << "...\n";
}

void TcpServer::accept_client() {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    while (true) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd >= 0) break;

        perror("⚠️ Accept failed — retrying...");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "🎉 Client connected from "
              << inet_ntoa(client_addr.sin_addr) << ":"
              << ntohs(client_addr.sin_port) << "\n";
}

void TcpServer::communicate() {
    char buffer[1024] = {0};
    int bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        std::cout << "📨 Received from client: " << buffer << "\n";

        std::string reply = std::string("Server received: ") + buffer;
        send(client_fd, reply.c_str(), reply.size(), 0);
    }
}
