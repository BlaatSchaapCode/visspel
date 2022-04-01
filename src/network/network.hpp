#pragma once

#if defined(_WIN32) || defined(__WIN32__)
#include <winsock2.h>
#include <ws2tcpip.h>

typedef SOCKET socket_t;
#define poll WSAPoll

#else
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef int socket_t;
#define closesocket close

#endif

#include <cstdint>
#include <string>
#include <vector>

namespace network {

class Connection;

int listen(const uint16_t port);
void connect(std::string ip_address, uint16_t port);

void init(void);
void deinit(void);
void process(void);

void on_disconnect(Connection *disconnection);
void on_connect_outgoing(Connection *outgoing_connection);
void on_connect_incoming(Connection *incoming_connection);

}; // namespace network
