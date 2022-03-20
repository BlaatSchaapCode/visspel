#pragma once

#if defined(_WIN32) || defined(__WIN32__)
#include <winsock2.h>
#include <ws2tcpip.h>

typedef SOCKET socket_t;
#else
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef int socket_t;

#define closesocket close
#endif

#include <cstdint>

namespace network {

int listen(const uint16_t port);

void init(void);
void deinit(void);
void process(void);

}; // namespace network
