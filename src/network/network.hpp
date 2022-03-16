#pragma once

#if defined(_WIN32) || defined(__WIN32__)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace network {
class Network {
  public:
    Network(void);
    ~Network(void);

  private:
#if defined(_WIN32) || defined(__WIN32__)
    WSADATA d;
#endif
};
}; // namespace network
