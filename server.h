#ifndef SERVER_H
#define SERVER_H

class TcpServer{
      public:
      TcpServer(int port);
      ~TcpServer();
      void run();

      private:
      int server_fd;
      int client_fd;
      int port;

      void setup_socket();
      void accept_client();
      void communicate();

      
};





#endif // SERVER_H