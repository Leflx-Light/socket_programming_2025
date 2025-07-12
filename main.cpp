// main.cpp
#include "server.h"
#include "client.h"
#include <thread>
#include <chrono>

int main() {
    // Run the server in a separate thread
    std::thread server_thread([]() {
        TcpServer server(8080);
        server.run();
    });

    // Give the server a moment to start
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Run client in main thread
    Client client("127.0.0.1", 8080);
    client.run();

    server_thread.join();
    return 0;
}
