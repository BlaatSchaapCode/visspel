#include "network.hpp"

#include <cstdint>
#include <cstring>

#include <iostream>
#include <string>
#include <vector>
#include <thread>



#include "iconnection.hpp"
#include "tcpconnection.hpp"

namespace network {

std::vector<iConnection *> connections;
std::thread * m_listenThread = nullptr;

// TODO: this must be atomic
bool active = false;

#if defined(_WIN32) || defined(__WIN32__)
WSADATA d = {0};
#endif

void init(void) {
#if defined(_WIN32) || defined(__WIN32__)
    if (WSAStartup(0x0202, &d)) {
        std::cerr << "Error initialising WinSock" << std::endl;
    }
#endif
    active = true;
}

void deinit(void) {
	active = false;

#if defined(_WIN32) || defined(__WIN32__)
    WSACleanup();
#endif

}



int listenThread(uint16_t port) {
	std::cout << "Requested to listen on port " << port << std::endl;

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
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    int no = 0;
    int yes = 1;
    if (setsockopt(listen_socket, IPPROTO_IPV6, IPV6_V6ONLY, (const char *)&no, sizeof(no))) {
        std::cerr << "Failed to set socket option" << std::endl;
        return -1;
    }

    if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes))) {
        std::cerr << "Failed to set socket option" << std::endl;
        return -1;
    }



    if (bind(listen_socket, (struct sockaddr *)&sin6_listen, sizeof(sin6_listen)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return -1;
    }

    if ( ::listen(listen_socket,0) < 0 ) {
    	std::cerr << "Error listening socket" << std::endl;
		return -1;
    }

    while (active) {
        struct sockaddr_in6 sin6_accept;
        socklen_t len_accept  = sizeof(sin6_accept);
        memset ( &sin6_accept, 0 , len_accept);

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
                std::cerr << "Error accepting socket" << std::endl;
            } else {
                std::cout << "Accepted Connection" << std::endl;
                connections.push_back(new TcpConnection(sin6_accept, sockfd_accept));
            }
        }
        if (poll_result < 0) {
            std::cerr << "Error polling socket" << std::endl;
            // There is an error
        } else {
            // Threre is a timeout.... nothing to do, just wait...and wait....
        }
        


        
    }
    std::cout << "Closing Listening Socket" << std::endl;
    closesocket (listen_socket);
    return 0;
}


int listen(const uint16_t port) {
	// This launched a new listen thread, and lets the
	// main loop continue.
	m_listenThread = new std::thread(listenThread,port);
	return 0;
}


void connect(std::string ip_address, uint16_t port) { 
    (void)port; 
    (void)ip_address;
}

void process(void) {}

}; // namespace network

