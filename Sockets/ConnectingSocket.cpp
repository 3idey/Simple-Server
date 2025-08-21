#include "ConnectingSocket.hpp"

HDE::ConnectingSocket::ConnectingSocket(int domain, int service,
                                        int protocol, int port, u_long interface) : SimpleSocket(domain, service, protocol, port, interface)
{
    connect_to_network(get_sock(), get_address());
}

void HDE::ConnectingSocket::connect_to_network(int sock,
                                              struct sockaddr_in address)
{
    test_connection(::connect(sock, (struct sockaddr *)&address, sizeof(address)));
}
