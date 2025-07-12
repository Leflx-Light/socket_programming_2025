# 📡 Socket Programming in Modern C++

This project is a simple example of **TCP Server & Client in Modern C++ (C++17)**, written in a clean, class-based way.  
It runs on Linux (tested on Ubuntu 24.04).  

Both the **server** and **client** are implemented using modern C++, split into separate `.h` and `.cpp` files.  
They communicate over a TCP socket — you type a message in the client, and the server responds.

---

## 🚀 Features

✅ TCP Server that listens on a port, accepts client connections, and replies.  
✅ TCP Client that connects to server, sends a message, and prints server reply.  
✅ Clean, easy-to-understand C++ classes (`Server`, `Client`).  
✅ Uses Linux sockets and standard C++ libraries.  
✅ Runs both server & client simultaneously using `std::thread`.

---

## 🗂️ Project Structure

| File/Folder     | Description                        |
|-----------------|------------------------------------|
| `server.h`      | Server class declaration           |
| `server.cpp`    | Server class implementation        |
| `client.h`      | Client class declaration           |
| `client.cpp`    | Client class implementation        |
| `main.cpp`      | Starts both server & client        |
| `README.md`     | This file (project documentation)  |


---

## 🔷 How it works

### Server
1️⃣ Creates a TCP socket with `socket()`.  
2️⃣ Binds it to a port with `bind()`.  
3️⃣ Starts listening with `listen()`.  
4️⃣ Waits for client with `accept()`.  
5️⃣ Reads message from client & sends a reply.  
6️⃣ Cleans up sockets when done.

### Client
1️⃣ Creates a TCP socket with `socket()`.  
2️⃣ Connects to the server with `connect()`.  
3️⃣ Reads your input from terminal.  
4️⃣ Sends it to server & prints server’s response.  
5️⃣ Cleans up sockets when done.

---

## 📄 Why these classes & functions?

### `Server` class
| Function | Purpose |
|----------|---------|
| `Server(int port)` | Constructor: stores port, initializes fds. |
| `~Server()` | Destructor: closes sockets. |
| `run()` | Public method to run everything: setup → accept → communicate. |
| `setup_socket()` | Creates, binds, listens. |
| `accept_client()` | Waits for client connection. |
| `communicate()` | Reads from client & sends reply. |

---

### `Client` class
| Function | Purpose |
|----------|---------|
| `Client(const std::string& host, int port)` | Constructor: stores server IP & port. |
| `~Client()` | Destructor: closes socket. |
| `run()` | Public method to connect & communicate. |
| `setup_connection()` | Creates & connects socket. |
| `communicate()` | Reads your input, sends to server, prints reply. |

---

## 📦 Why we included those headers?

| Header | Why? |
|--------|------|
| `<iostream>` | For `std::cout`, `std::cin`. |
| `<string>` | For `std::string`. |
| `<unistd.h>` | To use `close()`, `read()`, `write()`. |
| `<arpa/inet.h>` | For IP address functions (`inet_pton`, `inet_ntoa`). |
| `<sys/socket.h>` | To use sockets (`socket()`, `bind()`, etc.). |
| `<netinet/in.h>` | Defines `sockaddr_in` structure. |
| `<thread>` | To run server & client at the same time. |
| `<chrono>` | To wait a bit between starting server & client. |

---

## 🛠️ How to build & run

### Build
```bash
g++ -std=c++17 main.cpp server.cpp client.cpp -o tcp_example -pthread
