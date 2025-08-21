#include "SimpleSocket.hpp"

// Default constructor
HDE::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
    // Define address structure
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    // Establish socket
    sock = socket(domain, service, protocol);
    test_connection(sock);

    // Allow quick rebinding after restart
    int opt = 1;
    test_connection(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)));
#ifdef SO_REUSEPORT
    // Optional: allow multiple binds to same port (not critical)
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
#endif
}
// Test connection
void HDE::SimpleSocket::test_connection(int item_to_test)
{
    // confirm that the connection or socket has been established properly
    if (item_to_test < 0)
    {
        perror("Failed to connect...");
        exit(EXIT_FAILURE);
    }
}
// getter funcs
struct sockaddr_in HDE::SimpleSocket::get_address()
{
    return address;
}
int HDE::SimpleSocket::get_sock()
{
    return sock;
}
