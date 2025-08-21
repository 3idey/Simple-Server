#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
namespace HDE
{
    class SimpleSocket
    {
    private:
        struct sockaddr_in address;
        int sock;

    public:
        SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
        virtual void connect_to_network(int sock, struct sockaddr_in address) = 0;
        void test_connection(int connection);
        struct sockaddr_in get_address();
        int get_sock();
    };

}

#endif /*SimpleSocket_hpp*/