#include "network.hpp"

#include <cstdint>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "connection.hpp"
#include "protocol.hpp"
#include "tcpconnection.hpp"

#include "../utils/logger.hpp"

namespace network {

std::map<uint16_t, Connection *> clientConnections;

Connection *serverConnection;

std::thread *m_listenThread = nullptr;

// TODO: this must be atomic
bool active = false;

#if defined(_WIN32) || defined(__WIN32__)
WSADATA d = {0};
#endif

void init(void) {
#if defined(_WIN32) || defined(__WIN32__)
    if (WSAStartup(0x0202, &d)) {
        LOG_ERROR("Error initialising WinSock");
    }
#endif

    protocol_init();

    active = true;
}

void deinit(void) {
    active = false;

#if defined(_WIN32) || defined(__WIN32__)
    WSACleanup();
#endif
}

int listenThread(uint16_t port) {
    LOG_INFO("Requested to listen on port %d", port);

    // Note: IN6ADDR_ANY_INIT will listen to any IPv4 and IPv6 address
    // This means, it will listen on *ALL* interfaces.

    // https://docs.microsoft.com/en-us/windows/win32/winsock/dual-stack-sockets
    //
    // On Linux, it will listen to both IPv4 and IPv6 by default
    // On WIN32, it will listen on IPv6 only by default.
    // Enabling both IPv4 and IPv6 on the same socket requires at least Windows Vista
    // I doubt we require Windows XP support

    struct sockaddr_in6 sin6_listen = {
        .sin6_family = AF_INET6,
        .sin6_port = htons(port),
        .sin6_addr = IN6ADDR_ANY_INIT,
    };

    socket_t listen_socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (listen_socket < 0) {
        LOG_ERROR("Error creating socket");
        return -1;
    }

    int no = 0;
    int yes = 1;
    if (setsockopt(listen_socket, IPPROTO_IPV6, IPV6_V6ONLY, (const char *)&no, sizeof(no))) {
        LOG_ERROR("Failed to set socket option");
        return -1;
    }

    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes))) {
        LOG_ERROR("Failed to set socket option");
        return -1;
    }

    if (bind(listen_socket, (struct sockaddr *)&sin6_listen, sizeof(sin6_listen)) < 0) {
        LOG_ERROR("Error binding socket");
        return -1;
    }

    if (::listen(listen_socket, 0) < 0) {
        LOG_ERROR("Error listening socket");
        return -1;
    }

    while (active) {
        struct sockaddr_in6 sin6_accept;
        socklen_t len_accept = sizeof(sin6_accept);
        memset(&sin6_accept, 0, len_accept);

        const int nfds = 1;
        struct pollfd fds[nfds] = {{
            .fd = listen_socket,
            .events = POLLIN,
        }};
        const int timeout_ms = 100;

        int poll_result = poll(fds, nfds, timeout_ms);
        if (poll_result > 0) {
            // There is an incoming connection

            socket_t sockfd_accept = accept(listen_socket, (struct sockaddr *)&sin6_accept, &len_accept);
            if (sockfd_accept < 0) {
                LOG_ERROR("Error accepting socket");
            } else {
                LOG_INFO("Accepted Connection");

                // TODO :: let's make a map out of this rather then a vector
                // As we want to get the connection by its ID
                on_connect_incoming(new TcpConnection(sockfd_accept, sin6_accept));
            }
        }
        if (poll_result < 0) {
            LOG_ERROR("Error polling socket");
            // There is an error
        } else {
            // Threre is a timeout.... nothing to do, just wait...and wait....
        }
    }
    LOG_INFO("Closing Listening Socket");
    closesocket(listen_socket);
    return 0;
}

int listen(const uint16_t port) {
    // This launched a new listen thread, and lets the
    // main loop continue.
    m_listenThread = new std::thread(listenThread, port);
    return 0;
}

void connect(std::string ip_address, uint16_t port) {
    LOG_INFO("Requested to connect to %s:%d", ip_address.c_str(), port);

    struct sockaddr_in6 sin6_connect = {
        .sin6_family = AF_INET6,
        .sin6_port = htons(port),
    };

    struct sockaddr_in sin4_connect = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };

    socket_t connect_socket = 0;

    if (1 == inet_pton(AF_INET6, ip_address.c_str(), &sin6_connect.sin6_addr)) {
        connect_socket = socket(AF_INET6, SOCK_STREAM, 0);
        if (connect_socket < 0) {
            LOG_ERROR("Error creating socket");
            return;
        }
        if (connect(connect_socket, (struct sockaddr *)&sin6_connect, sizeof(sin6_connect)) < 0) {
            LOG_INFO("Failed to connect");
            return;
        }
    } else if (1 == inet_pton(AF_INET, ip_address.c_str(), &sin4_connect.sin_addr)) {
        connect_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (connect_socket < 0) {
            LOG_ERROR("Error creating socket");
            return;
        }
        if (connect(connect_socket, (struct sockaddr *)&sin4_connect, sizeof(sin4_connect)) < 0) {
            LOG_INFO("Failed to connect");
            return;
        }
        LOG_INFO("Connected");
        on_connect_outgoing(new TcpConnection(connect_socket));
    }
}

void on_connect_outgoing(Connection *outgoing_connection) { serverConnection = outgoing_connection; }

void on_connect_incoming(Connection *incoming_connection) {
    std::minstd_rand simple_rand;
    // Does it require C-style seeing?
    // If it is seeded on incoming connection, rather then on startup
    // Using the time in seconds has not enough resolution.
    // simple_rand.seed(time(NULL));
    uint16_t cid = simple_rand();
    incoming_connection->m_client_id = cid;
    clientConnections[cid] = incoming_connection;
    LOG_INFO("New incoming connection has been assigned Client ID %d", cid);
    set_connection_id(incoming_connection);
}

void on_disconnect(Connection *disconnection) {
    // We cannot stop the receiveThreadFunc thread from within the receiveThreadFunc
    // As, when the remote disconnects, we notice it in this thread
    // And therefore, on_disconnect will be called from there.
    // As such, we start a new thread to do the clean up
    auto on_disconnect_lambda = [disconnection]() {
        LOG_INFO("on disconnect called for connection %d", disconnection->m_client_id);
        if (disconnection == serverConnection) {
            LOG_INFO("This was the server connection");
            serverConnection = nullptr;
        } else {
            auto search = clientConnections.find(disconnection->m_client_id);
            if (search != clientConnections.end()) {
                LOG_INFO("This was a client connection");
                clientConnections.erase(disconnection->m_client_id);
            } else {
                LOG_ERROR("This was an unknown connection");
            }
        }
        delete disconnection;
    };
    std::thread cleanup_thread(on_disconnect_lambda); // Pass 10 to the lambda expression
    cleanup_thread.join();
}

void process(void) {}

}; // namespace network
