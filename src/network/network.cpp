#include "network.hpp"

#include <cstdint>
#include <string>

namespace network {

Network::Network(void) {
#if defined(_WIN32) || defined(__WIN32__)
    WSAStartup(0x0202, &d));
#endif
}

Network::~Network(void) {
#if defined(_WIN32) || defined(__WIN32__)
    WSACleanup();
#endif
}

void listen(uint16_t port) {}

void connect(std::string ip_address, uint16_t port) {}
}; // namespace network
