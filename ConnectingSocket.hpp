#ifndef connectingSocket_hpp
#define connectingSocket_hpp
#include "SimpleSocket.hpp"
#include <stdio.h>

namespace HDE
{
    class ConnectingSocket : public SimpleSocket
    {

    public:
        ConnectingSocket(int domain, int service,
                         int protocol, int port, u_long interface);
        int connect_to_network(int sock, struct sockaddr_in address);
    };

}
#endif