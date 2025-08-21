#include "TestServer.hpp"

HDE::TestServer::TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10)
{
    launch();
}

void HDE::TestServer::accepter()
{
    struct sockaddr_in
        address = get_socket()->get_address();
    int addlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(),
                        (struct sockaddr *)&address,
                        (socklen_t *)&addlen);
    read(new_socket, buffer, 30000);
}

void HDE::TestServer::handler()
{
    std::cout << buffer << std::endl;
}

void HDE::TestServer::responder()
{
    const char *body = "Hello from server";
    std::string resp = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: text/plain\r\n"
                       "Content-Length: " +
                       std::to_string(strlen(body)) + "\r\n"
                                                      "Connection: close\r\n"
                                                      "\r\n" +
                       std::string(body);
    write(new_socket, resp.c_str(), resp.size());
    close(new_socket);
}
void HDE::TestServer::launch()
{
    std::cout << "===== waiting ====== " << std::endl;
    accepter();
    handler();
    responder();
    std::cout << "===== DONE ====== " << std::endl;
}